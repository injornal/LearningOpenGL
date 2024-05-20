//
//  renderer.hpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#pragma once

#include <GL/glew.h>
#include <assert.h>
#include "vertexArray.hpp"
#include "indexBuffer.hpp"
#include "shaderProgram.hpp"

class Renderer
{
public:
    void draw(const VertexArray& VAO, const IndexBuffer& IBO, ShaderProgram& shader);
    inline void clear() const {glCall(glClear(GL_COLOR_BUFFER_BIT));}
};;
