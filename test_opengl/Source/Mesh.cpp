#include "Mesh.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

Mesh::Mesh(std::vector<Vertex>&& vertexs, std::vector<Texture>&& textures, std::vector<uint>&& indexs)
{
	m_vertexs = std::move(vertexs);
	m_textures = std::move(textures);
	m_indexs = std::move(indexs);

	SetupMesh();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);

	m_vertexs.clear();
	m_textures.clear();
	m_indexs.clear();
}

void Mesh::Draw(const GlProgram& shader)
{
	uint diffuseNr = 1;
	uint specularNr = 1;
	uint textureID = GL_TEXTURE0;
	for (auto& it : m_textures)
	{
		it.m_texture->Build(textureID);
		++textureID;

		std::string textureName;
		Texture::TextureType name = it.m_type;
		if (name == Texture::TextureType::eDiffuse)
		{
			textureName = "texture_diffuse" + std::to_string(diffuseNr++);
			shader.SetTextureUnit(it.m_texture, textureName);
		}
		/*else if (name == Texture::TextureType::eMirror)
			textureName = "texture_specular" + std::to_string(specularNr++);*/
	}

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indexs.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//float 
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	{
		int vboSize = 0;
		float* vbo = CreateData_VBO(vboSize);
		glBufferData(GL_ARRAY_BUFFER, vboSize * sizeof(float), vbo, GL_STATIC_DRAW);
		delete vbo;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexs.size() * sizeof(uint), &m_indexs[0], GL_STATIC_DRAW);

	//顶点位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_vertexs.at(0).Size(), (void*)0);
	glEnableVertexAttribArray(0);

	//法向量
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, m_vertexs.at(0).Size(), 
		(void*)(m_vertexs.at(0).m_position.Size() * sizeof(float)));
	glEnableVertexAttribArray(1);

	//纹理坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, m_vertexs.at(0).Size(),
		(void*)((m_vertexs.at(0).m_position.Size() + m_vertexs.at(0).m_normal.Size())
			* sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

float* Mesh::CreateData_VBO(int& size)
{
	int unitSize = 8;
	int nVertexSize = m_vertexs.size();
	size = nVertexSize * unitSize;
	float* res = new float[size];

	for (int i = 0; i < nVertexSize; ++i)
	{
		int offset = 0;
		for (int j = 0; j < m_vertexs[i].m_position.Size(); ++j)
		{
			res[i * unitSize + offset] = m_vertexs[i].m_position.At(j);
			++offset;
		}
		for (int j = 0; j < m_vertexs[i].m_normal.Size(); ++j)
		{
			res[i * unitSize + offset] = m_vertexs[i].m_normal.At(j);
			++offset;
		}
		for (int j = 0; j < m_vertexs[i].m_texCoords.Size(); ++j)
		{
			res[i * unitSize + offset] = m_vertexs[i].m_texCoords.At(j);
			++offset;
		}
	}

	return res;
}

