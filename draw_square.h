#pragma once
#ifndef DRAW_SQUARE_H
#define DRAW_SQUARE_H

#include <glad/glad.h>

void setupSquare(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO) {
    float verts[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    unsigned int indexes[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void drawSquare(unsigned int shaderProgram, unsigned int VAO, float x, float y, float scale, float r, float g, float b) {
    glUseProgram(shaderProgram);

    int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform4f(colorLoc, r, g, b, 1.0f);

    int offsetLoc = glGetUniformLocation(shaderProgram, "offset");
    glUniform2f(offsetLoc, x, y);

    int scaleLoc = glGetUniformLocation(shaderProgram, "scale");
    glUniform1f(scaleLoc, scale);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

#endif