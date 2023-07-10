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


/**
 * Class to handle shapes. They handle vertices, indices, buffers layout and arrays.
 */
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


/**
 * Create a square shape with 3D vertices, and texture coordinates, in the XY plane
 *
 * @param tx0
 * @param tx1
 * @param ty0
 * @param ty1
 * @return
 */
Shape createTextureQuad(float tx0, float tx1, float ty0, float ty1);


/**
 * Creates a square shape with 3D vertices, and texture coordinates, in the XY plane
 *
 * @return
 */
Shape createTextureQuad();

/**
 * Creates a cube with 3D vertices, normals, and colors
 *
 * @param r
 * @param g
 * @param b
 * @return
 */
Shape createColorNormalCube(float r, float g, float b);

/**
 * Creates the XYZ colored axis, with 3D vertices, expected to be uses with GL_LINES instead of triangles
 *
 * @param length
 * @return
 */
Shape createColorAxis(float length);

/**
 * Creates a noise map, with 3D vertices, normals and colors. Uses the water_level to color some vertices with blue.
 *
 * @param map
 * @param water_level
 * @return
 */
Shape createColorNoiseMap(const std::vector<std::vector<float>>& map, float water_level, int resolution);
