#include "StaticVertexBuffer.h"

StaticVertexBuffer::StaticVertexBuffer(GLsizei nSize)
	: VertexBuffer()
{
	CreateBuffer(nSize);
}

void StaticVertexBuffer::CreateBuffer(GLsizei nGroupLength)
{
	if (nGroupLength <= 0)
	{
		return;
	}

	if (!isValid())
	{
		glGenBuffers(1, &m_nVBOID);
	}
	
	m_nGroupLength = nGroupLength;
}

bool StaticVertexBuffer::wirteData(const float* dataPtr, size_t length)
{
	m_nLength = sizeof(float) * length;

	glBindBuffer(GL_ARRAY_BUFFER, m_nVBOID);

	glBufferData(GL_ARRAY_BUFFER, m_nLength, dataPtr, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return true;
}
