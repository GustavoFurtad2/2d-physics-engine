#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders.h"
#include "draw_square.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2d physics engine", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    unsigned int VAO, VBO, EBO;
    setupSquare(VAO, VBO, EBO);

    unsigned int shaderProgram = createShaderProgram("vertex_shader.glsl", "fragment_shader.glsl");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawSquare(shaderProgram, VAO, -0.3f, -0.3f, 0.5f, 1.0f, 0.0f, 0.0f);
        drawSquare(shaderProgram, VAO, 0.3f, 0.3f, 0.3f, 0.0f, 0.0f, 1.0f);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}