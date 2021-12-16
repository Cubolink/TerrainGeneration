//
// Created by major on 16-12-2021.
//

#pragma once

#include <string>
#include <utility>
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"
#include "indexbuffer.h"
#include "texture.h"

class Shape
{
private:
    const float* vertices;
    const unsigned int* indices;
    VertexArray vao;
    VertexBuffer vbo;
    VertexBufferLayout vbl;
    IndexBuffer ibo;

public:
    Shape(const float *vertices, unsigned int sizeof_vertices, const unsigned int *indices, unsigned int sizeof_indices);
    ~Shape();
    void Bind() const;

    void Unbind() const;

    inline unsigned int getIBOCount() const { return ibo.GetCount(); }
};

Shape createTextureQuad(float tx0, float tx1, float ty0, float ty1);

Shape createTextureQuad();
