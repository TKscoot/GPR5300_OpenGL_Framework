#include "Mesh.h"

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
	// TODO: Meshloading von Datei
}

void Mesh::Render()
{
	glUseProgram(mShaderProgram);

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
