//
//  vertexArray.hpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#pragma once
#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"

class VertexArray
{
private:
    unsigned int ID;
public:
    VertexArray();
    ~VertexArray();
    
    void bind() const;
    void unbind() const;
    
    void addBuffer(const VertexBuffer& VBO, const VertexBufferLayout& layout);
};
