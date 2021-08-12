#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/vector3.h>
#include <assimp/cimport.h>

Mesh::Mesh()
{
	mVertices =
	{					// Position			  // Normale
		Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f)},
		Vertex{glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f)},
		Vertex{glm::vec3( 0.0,   0.5f, 0.0f), glm::vec3(0.0f)}
	};

	mIndices = 
	{
		0, 1, 2
	};

	CreateOpenGLResources();
	LoadShader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");
}

Mesh::Mesh(string filename)
{
	unsigned int flags =
		aiProcess_Triangulate |
		aiProcess_GenNormals;

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, flags);

	if (!scene)
	{
		std::cout << "Mesh did not load correctly!" << std::endl;
		return;
	}

	if (!scene->HasMeshes())
	{
		std::cout << "Scene has no meshes!" << std::endl;
		return;
	}

	aiMesh* mesh = scene->mMeshes[0];

	mVertices.resize(mesh->mNumVertices);

	for (int v = 0; v < mesh->mNumVertices; v++)
	{

		// Position
		mVertices[v].position = glm::vec3(
								mesh->mVertices[v].x,
								mesh->mVertices[v].y,
								mesh->mVertices[v].z);
		// Normal
		mVertices[v].normal	  = glm::vec3(
								mesh->mNormals[v].x,
								mesh->mNormals[v].y,
								mesh->mNormals[v].z);
	}

	mIndices.resize(mesh->mNumFaces * 3);

	for (int f = 0; f < mesh->mNumFaces; f++)
	{
		aiFace* face = mesh->mFaces + f;
		for (int i = 0; i < face->mNumIndices; i++)
		{
			mIndices[((3 * f) + i)] = *(face->mIndices + i);
		}
	}

	CreateOpenGLResources();
	LoadShader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");
}

void Mesh::Render(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition)
{
	glUseProgram(mShaderProgram);

	UploadUniformMat4(mShaderProgram, "world", mWorld);
	UploadUniformMat4(mShaderProgram, "view", view);
	UploadUniformMat4(mShaderProgram, "projection", projection);

	UploadUniformVector3(mShaderProgram, "cameraPos", cameraPosition);

	glBindVertexArray(mVertexArrayObject);
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::CreateOpenGLResources()
{
	glGenVertexArrays(1, &mVertexArrayObject);

	glGenBuffers(1, &mVertexBufferObject);
	glGenBuffers(1, &mIndexBufferObject);

	glBindVertexArray(mVertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertices.size(), mVertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferObject);
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mIndices.size(), mIndices.data(), GL_STATIC_DRAW);

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
}

void Mesh::LoadShader(string vertexShaderFilepath, string fragmentShaderFilepath)
{
	// Vertex Shader Datei laden
	ifstream vertexStream(vertexShaderFilepath);
	stringstream vertexFileBuffer;
	vertexFileBuffer << vertexStream.rdbuf();
	string vertexShaderSourceString = vertexFileBuffer.str();
	const GLchar* vertexShaderSource = vertexShaderSourceString.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// Fragment Shader (Pixel Shader) Datei laden
	ifstream fragmentStream(fragmentShaderFilepath);
	stringstream fragmentFileBuffer;
	fragmentFileBuffer << fragmentStream.rdbuf();
	string fragmentShaderSourceString = fragmentFileBuffer.str();
	const GLchar* fragmentShaderSource = fragmentShaderSourceString.c_str();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	mShaderProgram = glCreateProgram();

	glAttachShader(mShaderProgram, vertexShader);
	glAttachShader(mShaderProgram, fragmentShader);

	glLinkProgram(mShaderProgram);
	
	glUseProgram(mShaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
