//
//  vertexBuffer.cpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#include "vertexBuffer.hpp"
#include "renderer.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glCall(glGenBuffers(1, &this->ID));
    this->bind();
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    glCall(glDeleteBuffers(1, &this->ID));
}

void VertexBuffer::bind() const
{
    
    glCall(glBindBuffer(GL_ARRAY_BUFFER, this->ID));
}

void VertexBuffer::unbind() const
{
    
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
