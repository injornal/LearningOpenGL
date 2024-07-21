//
//  shader.hpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class ShaderProgram
{
private:
    unsigned int ID;
    std::unordered_map<std::string, int> uniformLocationCache;
public:
    ShaderProgram(const std::string& filepath);
    ~ShaderProgram();
    
    void bind() const;
    void unbind() const;
    
    void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
    void setUniform1f(const std::string& name, float v1);
private:
    unsigned int compileShader(unsigned int type, const std::string& sourse);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
    ShaderProgramSource parseShader(const std::string& filepath);
    int getUniformLocation(const std::string& name);
};
