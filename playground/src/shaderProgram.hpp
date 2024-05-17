//
//  shader.hpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#pragma once
#include <string>
#include <unordered_map>

struct shaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class shaderProgram
{
private:
    unsigned int ID;
    std::unordered_map<std::string, int> uniformLocationCache;
public:
    shaderProgram(const std::string& filepath);
    ~shaderProgram();
    
    void bind() const;
    void unbind() const;
    
    void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
private:
    unsigned int compileShader(unsigned int type, const std::string& sourse);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
    shaderProgramSource parseShader(const std::string& filepath);
    int getUniformLocation(const std::string& name);
};
