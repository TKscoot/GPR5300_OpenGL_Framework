#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

inline bool GetKey(GLFWwindow* window, int key)
{
	auto state = glfwGetKey(window, key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

class Camera
{
public:

	Camera(GLFWwindow* window)
		: mWindow(window)
	{
		glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(glm::vec2 windowSize);

	glm::vec3 GetPosition() 
	{ 
		return mPosition; 
	}

	void Update(float deltatime);

private:
	void CalculateMouseDelta();
	void HandleKeyboardInput(float deltatime);

	GLFWwindow* mWindow = nullptr;

	glm::vec3 mPosition = glm::vec3(0.0f, 7.0f, 20.0f);
	glm::vec3 mFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float mYaw = -90.0f;
	float mPitch = 0.0f;

	float mLastX = 400.0f;
	float mLastY = 300.0f;

	bool mFirstMouseCheck = true;

	const float speed = 0.05f;
};