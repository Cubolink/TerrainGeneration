#pragma once


/**
 * VertexBuffer abstraction implementations.
 *
 * VertexBuffer Objects handle binding and unbinding the GL vertex buffer objects.
 */
class VertexBuffer
{
private:
	unsigned int m_RendererID;  // ID of the GL buffer generated
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};