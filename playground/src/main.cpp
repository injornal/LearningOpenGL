//
//  main.cpp
//  learn-opengl
//
//  Created by Kostiantyn Babich on 7/24/23.
//


/*
 Vertex shaders -- for each vertex
 Fragment shaders -- for each pixel
*/

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "renderer.hpp"
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "vertexArray.hpp"
#include "shaderProgram.hpp"



int main(void)
{
    GLFWwindow* window;

    /* Initialize GLFW */
    if (!glfwInit())
        return -1;

#ifdef __APPLE__
  /* We need to explicitly ask for a 3.2 context on OS X */
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(720, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Limit the frame rate */
    glfwSwapInterval(1);

    /* Initialze GLEW */
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }

    /* Print verlsions */
    std::cout<<glGetString(GL_VENDOR)<<std::endl;
    std::cout<<glGetString(GL_RENDERER)<<std::endl;
    std::cout<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
    
    
    float vertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,  0.5f,
        -0.5f, 0.5f
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    
    
    VertexArray VAO;
    VertexBuffer VBO(vertices, sizeof(vertices));
    
    VertexBufferLayout layout;
    layout.push<float>(2);
    VAO.addBuffer(VBO, layout);
    
    IndexBuffer IBO(indices, sizeof(indices) / sizeof(unsigned int));

    shaderProgram shaderProgram("res/shaders/sdf.shader");
    
    VAO.unbind();
    shaderProgram.unbind();
    VBO.unbind();
    IBO.unbind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        /* Draw call */
        shaderProgram.bind();
        VAO.bind();
        IBO.bind();
        
        shaderProgram.setUniform4f("uColor", 1, 1, 1, 1);
        
//        glCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr)); // USE FOR EXCEPTIONS
        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
