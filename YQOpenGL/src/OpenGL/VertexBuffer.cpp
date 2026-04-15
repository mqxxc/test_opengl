#include "../../include/OpenGL/VertexBuffer.h"

namespace YQ::OpenGL
{
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
}