#include "TextureUnit.h"

#include "glad/glad.h"
#include "stb_image.h"

#include <iostream>

TextureUnit::TextureUnit(uint nGlTexture)
{
	m_nGlTextureNum = nGlTexture;
	glGenTextures(1, &m_nTextureID);
}

TextureUnit::TextureUnit()
{
	m_nGlTextureNum = 0;
	glGenTextures(1, &m_nTextureID);
}

TextureUnit::~TextureUnit()
{
	glDeleteTextures(1, &m_nTextureID);
}

bool TextureUnit::LoadImg(const std::string& imgPath, bool reverseY)
{
	if (m_gTextureID != m_nTextureID)
	{
		m_gTextureID = m_nTextureID;

		glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	}

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(reverseY);
	unsigned char* data = stbi_load(imgPath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		else
			return false;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
		return true;
	}

	std::cout << "Failed to load texture" << std::endl;
	return false;
}

void TextureUnit::SetRowAround(Around around)
{
	SetParameteri(GL_TEXTURE_WRAP_S, around);
}

void TextureUnit::SetColumnAround(Around around)
{
	SetParameteri(GL_TEXTURE_WRAP_T, around);
}

void TextureUnit::SetAmplifyStrategy(Zoom zoom)
{
	SetParameteri(GL_TEXTURE_MIN_FILTER, zoom);
}

void TextureUnit::SetShrinkStrategy(Zoom zoom)
{
	SetParameteri(GL_TEXTURE_MAG_FILTER, zoom);
}

void TextureUnit::CreateGenerateMipmap()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}

bool TextureUnit::Build(uint nGlTexture)
{
	if (nGlTexture != 0)
	{
		m_nGlTextureNum = nGlTexture;
	}
	else if(m_nGlTextureNum == 0)
	{
		return false;
	}

	glActiveTexture(m_nGlTextureNum);
	glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	
	return true;
}

uint TextureUnit::TextureNum()
{
	return m_nGlTextureNum - GL_TEXTURE0;
}

void TextureUnit::SetParameteri(uint type, uint around)
{
	if (m_gTextureID != m_nTextureID)
	{
		m_gTextureID = m_nTextureID;

		glActiveTexture(m_nGlTextureNum);
		glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	}

	glTexParameteri(GL_TEXTURE_2D, type, around);
}


uint TextureUnit::m_gTextureID = 0;
