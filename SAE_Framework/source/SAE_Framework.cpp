#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Timer.h"
#include "Camera.h"

glm::vec2 windowSize = { 800.0f, 600.0f };

void InitGLFW()
{
    glfwInit();

    // OpenGL Version 4.5
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    windowSize.x = (float)width;
    windowSize.y = (float)height;
    glViewport(0, 0, windowSize.x, windowSize.y);
}

GLFWwindow* CreateWindow()
{
    GLFWwindow* window = 
        glfwCreateWindow(windowSize.x, windowSize.y, "SAE Framework", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    glfwSwapInterval(0); // deaktiviert V-Sync

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    return window;
}

void InitGLAD()
{
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

int main()
{
    GLFWwindow* window = nullptr;

    InitGLFW();

    window = CreateWindow();

    InitGLAD();

    glViewport(0, 0, windowSize.x, windowSize.y);

    glEnable(GL_DEPTH_TEST);

    Mesh triangleMesh;
    Mesh teapotMesh("teapot.obj");

    Camera camera(window);

    Timer timer;
    float deltatime = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        timer.Start();
        glfwPollEvents();

        camera.Update(deltatime);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view, projection;
        view = camera.GetViewMatrix();
        projection = camera.GetProjectionMatrix(windowSize);

        glm::vec3 camPos = camera.GetPosition();

        triangleMesh.Render(view, projection, camPos);
        teapotMesh.Render(view, projection, camPos);

        std::string title = "SAE Framework. FPS: " +
            std::to_string(1 / timer.ElapsedMilliseconds() * 1000) +
            " Deltatime: " + std::to_string(timer.ElapsedMilliseconds());

        glfwSetWindowTitle(window, title.c_str());

        glfwSwapBuffers(window);

        deltatime = timer.ElapsedMilliseconds();
        timer.Stop();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
