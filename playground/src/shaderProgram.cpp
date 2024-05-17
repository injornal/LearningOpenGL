//
//  shader.cpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#include "shaderProgram.hpp"
#include "renderer.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

unsigned int shaderProgram::compileShader(unsigned int type, const std::string& sourse)
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

unsigned int shaderProgram::createShader(const std::string& vertexShader, const std::string& fragmentShader)
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

shaderProgramSource shaderProgram::parseShader(const std::string& filepath)
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

shaderProgram::shaderProgram(const std::string& filepath)
{
    shaderProgramSource shaders = parseShader("res/shaders/sdf.shader");
    this->ID = createShader(shaders.vertexSource, shaders.fragmentSource);
}

shaderProgram::~shaderProgram()
{
    glCall(glDeleteProgram(ID));
}

void shaderProgram::bind() const
{
    glCall(glUseProgram(ID));
}

void shaderProgram::unbind() const
{
    glCall(glUseProgram(0));
}

void shaderProgram::setUniform4f(const std::string &name, float v1, float v2, float v3, float v4)
{
    glCall(glUniform4f(this->getUniformLocation(name), v1, v2, v3, v4));
}

int shaderProgram::getUniformLocation(const std::string& name)
{
    if(this->uniformLocationCache.find(name) != this->uniformLocationCache.end())
    {
        return this->uniformLocationCache.at(name);
    }
    glCall(int location = glGetUniformLocation(ID, name.c_str()));
    if (location == -1)
    {
        std::cout << "Warning: uniform " << name << " does not exist.";
    }
    this->uniformLocationCache[name] = location;
    return location;
}
