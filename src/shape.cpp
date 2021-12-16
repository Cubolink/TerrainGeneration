#include "shape.h"
#include "iostream"

Shape::Shape(const float *vertices, unsigned int vertices_count, const unsigned int *indices, unsigned int indices_count)
: vertices(vertices), indices(indices),
  vbo(vertices, vertices_count * sizeof (float)),
  ibo(indices, indices_count)
{
    std::cout << "Size of vertices: " << vertices_count * sizeof (float);
    std::cout << "\nSize of indices: " << indices_count << std::endl;
    vbl.Push<float>(3);  // position coordinates layout
    vbl.Push<float>(2);  // texture coordinates layout
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

    return {vertices, 20, indices, 6};
}

Shape createTextureQuad()
{
    return createTextureQuad(0, 1, 0, 1);
}