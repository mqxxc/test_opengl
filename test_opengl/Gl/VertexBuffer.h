#pragma once
#include "glad/glad.h"

class VertexBuffer
{
public:
	VertexBuffer();
	virtual ~VertexBuffer();

	virtual void CreateBuffer(GLsizei nGroupLength) = 0;
	inline bool isEmpty() const;
	inline GLsizeiptr dataLength() const;
	inline GLsizei groupLength() const;
	inline GLuint VBOID() const;
	inline bool isValid() const;

protected:
	GLuint m_nVBOID = 0;			//VBO ID
	GLsizei m_nGroupLength = 0;		// 一组数据的长度
	GLsizeiptr m_nLength = 0;		//buffer size
};

inline bool VertexBuffer::isEmpty() const
{
	return dataLength() == 0;
}

GLsizeiptr VertexBuffer::dataLength() const
{
	return m_nLength;
}

inline GLsizei VertexBuffer::groupLength() const
{
	return m_nGroupLength;
}

inline GLuint VertexBuffer::VBOID() const
{
	return m_nVBOID;
}

inline bool VertexBuffer::isValid() const
{
	return m_nVBOID != 0;
}

