//
//  indexBuffer.cpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#include "indexBuffer.hpp"
#include "renderer.hpp"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) : count(count)
{
    glCall(glGenBuffers(1, &this->rendererId));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererId));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    glCall(glDeleteBuffers(1, &this->rendererId));
}

void IndexBuffer::bind() const
{
    
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererId));
}

void IndexBuffer::unbind() const
{
    
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
