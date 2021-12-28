#pragma once

#include <vector>

/**
 * IndexBuffer abstraction implementations.
 * 
 * IndexBuffer Objects handle binding and unbinding the GL index buffer objects.
 */
class IndexBuffer
{
private:
	unsigned int m_RendererID;  // The ID of the generated buffer.
	unsigned int m_Count;  // Number of indices in the buffer.
public:
	explicit IndexBuffer(std::vector<unsigned int> &data);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }

    void updateData(std::vector<unsigned int> data);
};