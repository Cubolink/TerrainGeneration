//
// Created by major on 16-12-2021.
//

#pragma once

#include <string>
#include <utility>
#include <vector>
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"
#include "indexbuffer.h"
#include "texture.h"
#include "noise.h"

class Shape
{
private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    VertexArray vao;
    VertexBuffer vbo;
    VertexBufferLayout vbl;
    IndexBuffer ibo;

public:
    Shape(std::vector<float> vertices, std::vector<unsigned int> indices, const std::vector<int>& count_layouts);
    ~Shape();
    void Bind() const;

    void Unbind() const;

    inline unsigned int getIBOCount() const { return ibo.GetCount(); }

    Shape& operator= (Shape shape);

    std::vector<float> getVertices() { return vertices; }

    std::vector<unsigned int> getIndices() { return indices; }
};

Shape createTextureQuad(float tx0, float tx1, float ty0, float ty1);

Shape createTextureQuad();

Shape createColorNormalCube(float r, float g, float b);

Shape createColorAxis(float length);

Shape createColorNoiseMap(const std::vector<std::vector<float>>& map, float water_level);
