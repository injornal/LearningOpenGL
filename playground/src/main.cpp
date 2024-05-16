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


static unsigned int compileShader(unsigned int type, const std::string& sourse)
{
    unsigned int id = glCreateShader(type);
    const char* src = sourse.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    
    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

struct shaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

static shaderProgramSource parseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    
    return {ss[0].str(), ss[1].str()};
}

int main(void)
{
    assert(true);
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

    shaderProgramSource shaders = parseShader("res/shaders/sdf.shader");
    
    std::string vertexShader = shaders.vertexSource;
    std::string fragmentShader = shaders.fragmentSource;
    
    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);
    
    VAO.unbind();
    glUseProgram(0);
    VBO.unbind();
    IBO.unbind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        /* Draw call */
        glCall(glUseProgram(shader));
        
        VAO.bind();
        IBO.bind();
        
//        glCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr)); // USE FOR EXCEPTIONS
        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glDeleteProgram(shader);
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
