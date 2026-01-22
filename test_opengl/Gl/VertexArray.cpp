#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_nVAOID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_nVAOID);
}

void VertexArray::setupVBO(const std::vector<VertexLayout>& VertexLayoutList)
{
	glBindVertexArray(m_nVAOID);

	int attributeIndex = 0;

	for (auto& it : VertexLayoutList)
	{
		glBindBuffer(GL_ARRAY_BUFFER, it.VBO->VBOID());
		glVertexAttribPointer(attributeIndex, it.attributeLength, it.dataTypeEnum,
			(it.normalized ? GL_TRUE : GL_FALSE), it.VBO->groupLength() * it.unitLength, (void*)(it.offset * it.unitLength));
		glEnableVertexAttribArray(attributeIndex);
		++attributeIndex;
	}

	glBindVertexArray(0);
}
