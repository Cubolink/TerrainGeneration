#include "renderer.h"

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	shader.Bind();
	vao.Bind();
	ibo.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));

	// We should unbind, but we're not doing it because when binding other things it will be like the same.
	// So, unbinding may low a little the performance. But, it may fix some errors we could have.
	// We are not doing it, but we should.
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}