//
//  indexBuffer.hpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#pragma once

class IndexBuffer
{
private:
    unsigned int ID;
    unsigned int count;
public:
    IndexBuffer(const void* data, unsigned int count);
    ~IndexBuffer();
    
    void bind() const;
    void unbind() const;
    
    inline unsigned int getCount() const { return this->count; }
};
