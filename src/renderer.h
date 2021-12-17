#pragma once

#include "glerrorhandler.h"

//#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "texture.h"
#include "shape.h"

class Renderer
{
public:
	void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
    void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Texture& texture, const Shader& shader) const;
    void Draw(const Shape& shape, const Texture& texture, const Shader& shader) const;
    void Draw(const Shape& shape, const Texture& texture, const Shader& shader, int gl_mode) const;

	void Clear() const;
};