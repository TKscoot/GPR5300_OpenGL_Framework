#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

inline void UploadUniformMat4(GLuint shaderProgram, const GLchar* name, glm::mat4 value)
{
	GLint location = glGetUniformLocation(shaderProgram, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

inline void UploadUniformVector3(GLuint shaderProgram, const GLchar* name, glm::vec3 value)
{
	GLint location = glGetUniformLocation(shaderProgram, name);
	glUniform3f(location, value.x, value.y, value.z);
}

