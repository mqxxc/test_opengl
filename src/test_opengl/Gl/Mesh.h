#pragma once
#include "Vec3.hpp"
#include "pch.h"

#include "GlProgram.h"
#include "TextureUnit.h"


#include <vector>

class Vertex
{
public:
	YQ::Vec3f m_position;	//顶点
	YQ::Vec3f m_normal;		//法向量
	YQ::Vec2f m_texCoords;	//纹理坐标

	int Size() const
	{
		return m_position.Size() * sizeof(float)
			+ m_normal.Size() * sizeof(float)
			+ m_texCoords.Size() * sizeof(float);
	}
};

class Texture
{
public:
	enum class TextureType : unsigned short
	{
		eNone = 0,
		eDiffuse,
		eMirror
	};
	TextureUnit* m_texture;	//纹理
	TextureType m_type;		//纹理类型
};

class Mesh
{
public:
	std::vector<Vertex> m_vertexs;
	std::vector<Texture> m_textures;
	std::vector<uint> m_indexs;

	Mesh(std::vector<Vertex>&& vertexs, std::vector<Texture>&& textures, 
		std::vector<uint>&& indexs);
	~Mesh();

	void Draw(const GlProgram& shader);

private:
	uint m_VAO;
	uint m_VBO;
	uint m_EBO;

	void SetupMesh();

	float* CreateData_VBO(int & size);
};

