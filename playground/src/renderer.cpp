//
//  renderer.cpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#include "renderer.hpp"
#include "errorHandler.hpp"
#include <GL/glew.h>


void Renderer::draw(const VertexArray &VAO, const IndexBuffer &IBO, ShaderProgram &shader)
{
    shader.bind();
    VAO.bind();
    IBO.bind();
    
    glCall(glDrawElements(GL_TRIANGLES, IBO.getCount(), GL_UNSIGNED_INT, nullptr));
}
