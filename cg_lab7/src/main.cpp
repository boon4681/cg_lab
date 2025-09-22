#undef GLFW_DLL
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <cmath>

#include "Libs/Shader.h"
#include "Libs/Window.h"
#include "Libs/Mesh.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLint WIDTH = 800, HEIGHT = 600;

Window mainWindow;
std::vector<Mesh *> meshList;
std::vector<Shader> shaderList;

// Vertex Shader
static const char *vShader = "Shaders/shader.vert";

// Fragment Shader
static const char *fShader = "Shaders/shader.frag";

void CreateTriangle()
{
    GLfloat vertices[] =
        {
            -1.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f};

    unsigned int indices[] =
        {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2};
    Mesh *obj = new Mesh();
    obj->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj);
}

void CreateShaders()
{
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main()
{
    mainWindow = Window(WIDTH, HEIGHT, 3, 3);
    mainWindow.initialise();

    CreateTriangle();
    CreateTriangle();
    CreateShaders();

    GLuint uniformModel = 0, uniformProjection = 0;

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    // Loop until window closed
    while (!mainWindow.getShouldClose())
    {
        // Get + Handle user input events
        glfwPollEvents();

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw here
        shaderList[0].UseShader();

        uniformModel = shaderList[0].GetUniformLocation("model");
        uniformProjection = shaderList[0].GetUniformLocation("projection");

        // Object
        // obj 1
        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(0.3f, 0.0f, -2.5f));
            // model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

            meshList[0]->RenderMesh();
        }
        // obj 2
        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(-0.3f, -0.3f, -2.5f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

            meshList[1]->RenderMesh();
        }
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

        glUseProgram(0);
        // end draw

        mainWindow.swapBuffers();
    }

    return 0;
}
