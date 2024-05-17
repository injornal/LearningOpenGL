//
//  vertexArray.cpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#include "vertexArray.hpp"
#include "renderer.hpp"

VertexArray::VertexArray()
{
    glCall(glGenVertexArrays(1, &this->ID));
}

VertexArray::~VertexArray()
{
    glCall(glDeleteVertexArrays(1, &this->ID));
}

void VertexArray::bind() const
{
    glBindVertexArray(this->ID);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer &VBO, const VertexBufferLayout &layout)
{
    this->bind();
    VBO.bind();
    const auto& elements = layout.getElements();
    unsigned long offset = 0;
    for(int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}
