#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Helper.h"

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

	void Render(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition);

private:
	void CreateOpenGLResources();

	void LoadShader(string vertexShaderFilepath, string fragmentShaderFilepath);


	vector<Vertex> mVertices{};
	vector<int>    mIndices;

	glm::mat4 mWorld = glm::mat4(1.0f);

	GLuint mVertexBufferObject = 0;
	GLuint mIndexBufferObject  = 0;
	GLuint mVertexArrayObject  = 0;

	GLuint mShaderProgram = 0;

};