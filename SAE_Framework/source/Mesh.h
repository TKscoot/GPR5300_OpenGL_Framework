#pragma once
#include <vector>
#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<float> vertices, std::vector<int> indices);
	Mesh(std::string filename);

	void Draw();

private:
	void CreateOpenGLResources();
	void LoadShader(std::string vertexPath, std::string fragmentPath);

	std::vector<float> mVertices = {};
	std::vector<int>   mIndices  = {};

	GLuint mVertexBufferObject = 0;
	GLuint mIndexBufferObject  = 0;
	GLuint mVertexArrayObject  = 0;

	GLuint mShaderProgram  = 0;
};