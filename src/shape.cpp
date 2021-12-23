#include <iostream>
#include "shape.h"
#include "color.h"

Shape::Shape(const float *vertices, unsigned int vertices_count, const unsigned int *indices, unsigned int indices_count, const std::vector<int>& count_layouts)
: vertices(vertices), indices(indices),
  vbo(vertices, vertices_count * sizeof (float)),
  ibo(indices, indices_count)
{
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

Shape createColorNoiseMap(const std::vector<std::vector<float>>& map)
{
    long long int w = map.size();
    long long int h = map[0].size();
    auto *vertices = new float[w * h * 9];
    float max_z = 0, min_z = 0;
    for (long long int x = 0; x < w; x++)
    {
        for (long long int y = 0; y < h; y++)
        {
            vertices[9*(h*x + y)] = (float) x;
            vertices[9*(h*x + y) + 1] = (float) y;
            vertices[9*(h*x + y) + 2] = map[x][y];
            if (map[x][y]  > max_z)
                max_z = map[x][y];
            if (map[x][y] < min_z)
                min_z = map[x][y];
        }
    }
    float range = max_z - min_z;
    float hue;
    for (long long int x = 0; x < w; x++)
    {
        for (long long int y = 0; y < h; y++)
        {
            hue = 240 * (map[x][y] - min_z) / range;
            Color::RGB color = Color::hsv_to_rgb({240 - hue, 1.f, 0.5f});

            // falta la asignación de colores también
            vertices[9*(h*x + y) + 3] = color.r;
            vertices[9*(h*x + y) + 4] = color.g;
            vertices[9*(h*x + y) + 5] = color.b;
            // faltan las normales, temporalmente todas apuntarán hacia arriba, independientemente de la inclinación
            vertices[9*(h*x + y) + 6] = .0f;
            vertices[9*(h*x + y) + 7] = .0f;
            vertices[9*(h*x + y) + 8] = 1.0f;
        }
    }
    std::vector<unsigned int> v_indices;
    for (long long int x = 1; x < w; x++)
    {
        for (long long int y = 1; y < h; y++)
        {
            long long int i0 = h*(x-1) + (y-1);
            long long int i1 = h*x + (y-1);
            long long int i2 = h*x + y;
            long long int i3 = h*(x-1) + y;
            v_indices.push_back(i0);
            v_indices.push_back(i1);
            v_indices.push_back(i2);
            v_indices.push_back(i2);
            v_indices.push_back(i3);
            v_indices.push_back(i0);
        }
    }
    auto *indices = new unsigned int [v_indices.size()];
    for (int i = 0; i < v_indices.size(); i++)
    {
        indices[i] = v_indices[i];
    }
    std::vector<int> count_layouts;
    count_layouts.push_back(3);
    count_layouts.push_back(3);
    count_layouts.push_back(3);
    return {vertices, static_cast<unsigned int>((unsigned int) w * h * 9), indices, v_indices.size(), count_layouts};


}