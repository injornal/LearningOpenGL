//
//  vertexBufferLayout.hpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#pragma once
#include <vector>
#include <assert.h>
#include "renderer.hpp"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    bool normalized;
    
    static unsigned int getSizeOfType(unsigned int type)
    {
        switch (type) {
            case GL_FLOAT:
                return sizeof(GLfloat);
            case GL_UNSIGNED_INT:
                return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:
                return sizeof(GLubyte);
        }
        assert(false);
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;
    
public:
    VertexBufferLayout(): stride(0) {}
    
    template<typename T>
    void push(unsigned int count)
    {
        assert(false);
    }
    
    template<>
    void push<float>(unsigned int count)
    {
        this->elements.push_back({ GL_FLOAT, count, GL_FALSE });
        this->stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
    }
    
    inline const std::vector<VertexBufferElement> getElements() const { return this->elements; }
    inline unsigned int getStride() const { return this->stride; }
};
