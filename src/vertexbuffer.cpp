#include "vertexbuffer.h"

#include "glerrorhandler.h"


/**
* Default constructor for VertexBuffer. Generates a GL (Array) Buffer.
*
* @param data Pointer to the index data array, which contains the indices.
* @param size Size (in bytes) of the index data.
*/
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID);  // Tells GL to generate 1 Buffer, and store its id in m_RendererID.
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);  // Binds an Array Buffer to the generated buffer.
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);  // Tells GL that the binded buffer has some characteristics.
}

/**
* Default destructor of VertexBuffer.
* Tells GL to delete the buffer.
*/
VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

/**
* Tells GL to bind the index buffer.
*/
void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

/**
* Tells GL to unbind the index buffer.
*/
void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}