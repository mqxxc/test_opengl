#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
	if (isValid())
	{
		glDeleteBuffers(1, &m_nVBOID);
	}
}
