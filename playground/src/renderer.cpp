//
//  renderer.cpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#include "renderer.hpp"
#include <iostream>

void glClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function)
{
    while(GLenum error = glGetError()) {
        std::cout << "[OpenGL] Error(" << error << ") " << function << std::endl; // << function << " " << file << "line: " << line << std::endl;
        return false;
    }
    return true;
}
