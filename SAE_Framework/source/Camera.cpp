#include "Camera.h"

glm::mat4 Camera::GetViewMatrix()
{
	glm::vec3 lookPos = mPosition + mFront;
	return glm::lookAt(mPosition, lookPos, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::GetProjectionMatrix(glm::vec2 windowSize)
{
	return glm::perspective(glm::radians(45.0f), windowSize.x / windowSize.y, 0.1f, 100.0f);
}

void Camera::Update(float deltatime)
{
	HandleKeyboardInput(deltatime);

	CalculateMouseDelta();
}

void Camera::CalculateMouseDelta()
{
	double xpos, ypos;
	glfwGetCursorPos(mWindow, &xpos, &ypos);

	if (mFirstMouseCheck)
	{
		mLastX = xpos;
		mLastY = ypos;
		mFirstMouseCheck = false;
	}

	glm::vec2 mouseDelta = glm::vec2(0.0f);
	mouseDelta.x = xpos - mLastX;
	mouseDelta.y = mLastY - ypos;

	mYaw += mouseDelta.x * 0.2f; // 0.2f = sensitivity
	mPitch += mouseDelta.y * 0.2f; // 0.2f = sensitivity

	if (mPitch > 89.0f)
	{
		mPitch = 89.0f;
	}
	if (mPitch < -89.0f)
	{
		mPitch = -89.0f;
	}

	glm::vec3 front = glm::vec3(1.0f);

	front.x = glm::cos(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
	front.y = glm::sin(glm::radians(mPitch));
	front.z = glm::sin(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));

	mFront = glm::normalize(front);

	mLastX = xpos;
	mLastY = ypos;
}

void Camera::HandleKeyboardInput(float deltatime)
{
	if (GetKey(mWindow, GLFW_KEY_W))
	{
		mPosition += speed * mFront * deltatime;
	}
	if (GetKey(mWindow, GLFW_KEY_S))
	{
		mPosition -= speed * mFront * deltatime;
	}
	if (GetKey(mWindow, GLFW_KEY_A))
	{
		mPosition -= glm::normalize(glm::cross(mFront, mUp)) * speed * deltatime;
	}
	if (GetKey(mWindow, GLFW_KEY_D))
	{
		mPosition += glm::normalize(glm::cross(mFront, mUp)) * speed * deltatime;
	}
}
