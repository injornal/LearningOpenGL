//
//  vertexBuffer.hpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#pragma once

class VertexBuffer 
{
private:
    unsigned int rendererId;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    
    void bind() const;
    void unbind() const;
};
