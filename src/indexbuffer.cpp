#include "indexbuffer.h"

#include "glerrorhandler.h"


/**
* Default constructor for IndexBuffer. Generates a GL (ELEMENT ARRAY) Buffer. It assumes they contain unsigned ints.
* 
* @param data Pointer to the index data array, which contains the indices.
* @param count Number of indices in the index data.
*/
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GLCall(glGenBuffers(1, &m_RendererID));  // Tells GL to generate 1 Buffer, and store its id in m_RendererID.
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));  // Binds an Element Array Buffer to the generated buffer.
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));  // Tells GL that the binded buffer has some characteristics.
}

/**
* Default destructor of IndexBuffer.
* Tells GL to delete the buffer.
*/
IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID))
}

/**
* Tells GL to bind the index buffer.
*/
void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

/**
* Tells GL to unbind the index buffer.
*/
void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}