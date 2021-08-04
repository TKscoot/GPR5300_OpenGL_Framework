#include "Mesh.h"

Mesh::Mesh()
{
    mVertices.clear();
	mVertices = 
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    mIndices.clear();
    mIndices = {
        0, 1, 2
    };

    CreateOpenGLResources();
    LoadShader("shaders/DefaultVert.vert", "shaders/DefaultFrag.frag");
}

Mesh::Mesh(std::vector<float> vertices, std::vector<int> indices)
    : mVertices(vertices)
    , mIndices(indices)
{
    CreateOpenGLResources();
    LoadShader("shaders/DefaultVert.vert", "shaders/DefaultFrag.frag");
}

Mesh::Mesh(std::string filename)
{
    // TODO
}

void Mesh::Draw()
{
    glUseProgram(mShaderProgram);
    glBindVertexArray(mVertexArrayObject);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::CreateOpenGLResources()
{
    // Vertex Array
    glGenVertexArrays(1, &mVertexArrayObject);

    // Vertex Buffer & Index Buffer creation
    glGenBuffers(1, &mVertexBufferObject);
    glGenBuffers(1, &mIndexBufferObject);

    glBindVertexArray(mVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mVertices.size(), mVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mIndices.size(), mIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void Mesh::LoadShader(std::string vertexPath, std::string fragmentPath)
{
    // Vertex Shader
    std::ifstream vertexStream(vertexPath);
    std::stringstream vertexFileBuffer;
    vertexFileBuffer << vertexStream.rdbuf();
    std::string vertexShaderSourceString = vertexFileBuffer.str();
    const GLchar* vertexShaderSource = vertexShaderSourceString.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Fragment Shader
    std::ifstream fragmentStream(fragmentPath);
    std::stringstream fragmentFileBuffer;
    fragmentFileBuffer << fragmentStream.rdbuf();
    std::string fragmentShaderSourceString = fragmentFileBuffer.str();
    const GLchar* fragmentShaderSource = fragmentShaderSourceString.c_str();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);


    // Linking our shaders to the shader program
    mShaderProgram = glCreateProgram();
    
    glAttachShader(mShaderProgram, vertexShader);
    glAttachShader(mShaderProgram, fragmentShader);
    
    glLinkProgram(mShaderProgram);

    glUseProgram(mShaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}