#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Timer.h"

void InitGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void InitGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* CreateWindow(int width, int height) 
{
    GLFWwindow* window = glfwCreateWindow(width, height, "SAE Framework", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // disables VSync

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    return window;
}

int main()
{
    GLFWwindow* window;

    int width = 800, height = 600;

    InitGLFW();

    window = CreateWindow(width, height);

    InitGlad();

    glViewport(0, 0, width, height);

    Mesh triangleMesh;
    Timer t;
    

    while (!glfwWindowShouldClose(window))
    {
        t.Start();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        triangleMesh.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

        std::string title = "SAE Framework. FPS: " 
            + std::to_string(1 / t.ElapsedMilliseconds() * 1000)
            + " Frametime: " + std::to_string(t.ElapsedMilliseconds());

        glfwSetWindowTitle(window, title.c_str());

        t.Stop();
    }

    glfwTerminate();
}
