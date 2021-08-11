#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

class Mesh
{
public:
	Mesh();
	Mesh(string filename);

	void Render();

private:
	void CreateOpenGLResources();

	void LoadShader(string vertexShaderFilepath, string fragmentShaderFilepath);


	vector<Vertex> mVertices{};
	vector<int>    mIndices;

	GLuint mVertexBufferObject = 0;
	GLuint mIndexBufferObject  = 0;
	GLuint mVertexArrayObject  = 0;

	GLuint mShaderProgram = 0;

};