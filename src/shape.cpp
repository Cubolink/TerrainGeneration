#include "shape.h"
#include "iostream"

Shape::Shape(const float *vertices, unsigned int vertices_count, const unsigned int *indices, unsigned int indices_count, const std::vector<int>& count_layouts)
: vertices(vertices), indices(indices),
  vbo(vertices, vertices_count * sizeof (float)),
  ibo(indices, indices_count)
{
    std::cout << "Size of vertices: " << vertices_count * sizeof (float);
    std::cout << "\nSize of indices: " << indices_count << std::endl;
    for (int i: count_layouts)
    {
        vbl.Push<float>(i);  // ex: position coordinates layout, then color or texture, etc
    }
    vao.AddBuffer(vbo, vbl);
}

Shape::~Shape()
{
    delete[] vertices;
    delete[] indices;
}

void Shape::Bind() const
{
    vao.Bind();
    vbo.Bind();
    ibo.Bind();
}

void Shape::Unbind() const
{
    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
}

Shape createTextureQuad(float tx0, float tx1, float ty0, float ty1)
{
    auto* vertices = new float[20] {
            -0.5f, -0.5f, 0.0f, tx0, ty0,
            0.5f, -0.5f, 0.0f, tx1, ty0,
            0.5f, 0.5f, 0.0f, tx1, ty1,
            -0.5f, 0.5f, 0.0f, tx0, ty1

    };
    auto* indices = new unsigned int[6] {
            0, 1, 2,
            2, 3, 0
    };
    std::vector<int> count_layouts;
    count_layouts.push_back(3);
    count_layouts.push_back(2);

    return {vertices, 20, indices, 6, count_layouts};
}

Shape createTextureQuad()
{
    return createTextureQuad(0, 1, 0, 1);
}

Shape createColorNormalCube(float r, float g, float b) {
    auto *vertices = new float[216] {
        // Z+
        -0.5, -0.5,  0.5, r, g, b,   0, 0, 1,
        0.5,  -0.5,  0.5, r, g, b,   0, 0, 1,
        0.5,   0.5,  0.5, r, g, b,   0, 0, 1,
        -0.5,  0.5,  0.5, r, g, b,   0, 0, 1,

        // Z-
        -0.5, -0.5, -0.5, r, g, b,   0, 0, -1,
        0.5,  -0.5, -0.5, r, g, b,   0, 0, -1,
        0.5,   0.5, -0.5, r, g, b,   0, 0, -1,
        -0.5,  0.5, -0.5, r, g, b,   0, 0, -1,

        // X+
        0.5, -0.5, -0.5, r, g, b,   1, 0, 0,
        0.5,  0.5, -0.5, r, g, b,   1, 0, 0,
        0.5,  0.5,  0.5, r, g, b,   1, 0, 0,
        0.5, -0.5,  0.5, r, g, b,   1, 0, 0,

        // X-
        -0.5, -0.5, -0.5, r, g, b,  -1, 0, 0,
        -0.5,  0.5, -0.5, r, g, b,  -1, 0, 0,
        -0.5,  0.5,  0.5, r, g, b,  -1, 0, 0,
        -0.5, -0.5,  0.5, r, g, b,  -1, 0, 0,

        // Y+
        -0.5, 0.5, -0.5, r, g, b,  0, 1, 0,
        0.5,  0.5, -0.5, r, g, b,  0, 1, 0,
        0.5,  0.5,  0.5, r, g, b,  0, 1, 0,
        -0.5, 0.5,  0.5, r, g, b,  0, 1, 0,

        // Y-
        -0.5, -0.5, -0.5, r, g, b,  0, -1, 0,
        0.5,  -0.5, -0.5, r, g, b,  0, -1, 0,
        0.5,  -0.5,  0.5, r, g, b,  0, -1, 0,
        -0.5, -0.5,  0.5, r, g, b,  0, -1, 0
    };
    auto *indices = new unsigned int[36] {
        0,  1,   2,  2,  3,  0,  // Z+
        7,  6,   5,  5,  4,  7,  // Z-
        8,  9,  10, 10, 11,  8,  // X+
        15, 14, 13, 13, 12, 15,  // X-
        19, 18, 17, 17, 16, 19,  // Y+
        20, 21, 22, 22, 23, 20  // Y-
    };
    std::vector<int> count_layouts;
    count_layouts.push_back(3);
    count_layouts.push_back(3);
    count_layouts.push_back(3);
    return {vertices, 216, indices, 36, count_layouts};
}

Shape createColorAxis(float length) {
    auto *vertices = new float[42] {
        -length, .0f, .0f, .0f, .0f, .0f, 1.f,
        length, .0f, .0f, 1.f, .0f, .0f, 1.f,

        .0f, -length, .0f, .0f, .0f, .0f, 1.f,
        .0f, length, .0f, .0f, .1f, .0f, 1.f,

        .0f, .0f, -length, .0f, .0f, .0f, 1.f,
        .0f, .0f, length, .0f, .0f, .1f, 1.f
    };
    auto *indices = new unsigned int[6] {
        0, 1,
        2, 3,
        4, 5
    };
    std::vector<int> count_layouts;
    count_layouts.push_back(3);
    count_layouts.push_back(4);

    return {vertices, 42, indices, 6, count_layouts};
}

