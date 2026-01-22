#pragma once
#include "glad/glad.h"
#include "VertexBuffer.h"

#include <Vector>

class VertexArray
{
public:
	struct VertexLayout
	{
		VertexBuffer* VBO =  nullptr;		//VBO对象
		GLint attributeLength = 0;			//VBO中一组描述属性数据的长度
		GLenum dataTypeEnum = GL_FLOAT;		//数据类型
		bool normalized = false;			//是否需要归一化数据
		size_t offset = 0;					//偏移步长
		GLint unitLength = 0;				//一个数据的长度
	};

	VertexArray();
	virtual ~VertexArray();

	void setupVBO(const std::vector<VertexLayout>& VertexLayoutList);

	inline void bindVertexArray();

protected:
	GLuint m_nVAOID = 0;
};

void VertexArray::bindVertexArray()
{
	glBindVertexArray(m_nVAOID);
}
