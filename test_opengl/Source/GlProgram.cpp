#include "GlProgram.h"
#include "Shader.h"
#include "TextureUnit.h"

#include "glad/glad.h"
#include <iostream>

GlProgram::GlProgram()
{
	m_nProgramID = glCreateProgram();
}

GlProgram::~GlProgram()
{
	glDeleteProgram(m_nProgramID);
}

void GlProgram::CreateVertexShader(const std::vector<std::string>& Source)
{
	Shader* pShader = Shader::CreateVertexShader();
	if (pShader->LoadFromString(Source) != 0)
	{
		std::cout << "VertexShader create error" << std::endl;
	}
	else
	{
		m_listShader.push_back(pShader);
	}
}

void GlProgram::CreateVertexShader(const std::string& Source)
{
	Shader* pShader = Shader::CreateVertexShader();
	if (pShader->LoadFromString(Source) != 0)
	{
		std::cout << "VertexShader create error" << std::endl;
	}
	else
	{
		m_listShader.push_back(pShader);
	}
}

void GlProgram::CreateVertexShaderFromFile(const std::string& strFile)
{
	Shader* pShader = Shader::CreateVertexShader();
	if (pShader->LoadFromFile(strFile) != 0)
	{
		std::cout << "VertexShader create error" << std::endl;
	}
	else
	{
		m_listShader.push_back(pShader);
	}
}

void GlProgram::CreateVertexShaderFromFile(const std::vector<std::string>& strFile)
{
}

void GlProgram::CreateFragmentShader(const std::vector<std::string>& Source)
{
	Shader* pShader = Shader::CreateFragmentShader();
	if (pShader->LoadFromString(Source) != 0)
	{
		std::cout << "FragmentShader create error" << std::endl;
	}
	else
	{
		m_listShader.push_back(pShader);
	}
}

void GlProgram::CreateFragmentShader(const std::string& Source)
{
	Shader* pShader = Shader::CreateFragmentShader();
	if (pShader->LoadFromString(Source) != 0)
	{
		std::cout << "FragmentShader create error" << std::endl;
	}
	else
	{
		m_listShader.push_back(pShader);
	}
}

void GlProgram::CreateFragmentShaderFromFile(const std::string& strFile)
{
	Shader* pShader = Shader::CreateFragmentShader();
	if (pShader->LoadFromFile(strFile) != 0)
	{
		std::cout << "FragmentShader create error" << std::endl;
	}
	else
	{
		m_listShader.push_back(pShader);
	}
}

void GlProgram::CreateFragmentShaderFromFile(const std::vector<std::string>& strFile)
{
}

bool GlProgram::Complete()
{
	if (m_nProgramID == -1)
	{
		return false;
	}

	for (auto it : m_listShader)
	{
		glAttachShader(m_nProgramID, it->ShaderID());
	}
	glLinkProgram(m_nProgramID);

	for (auto it : m_listShader)
	{
		delete it;
	}
	m_listShader.clear();

	return true;
}

void GlProgram::SetTextureUnit(TextureUnit* tex, const std::string& varName)
{
	glUniform1i(glGetUniformLocation(m_nProgramID, varName.c_str()), tex->m_nGlTextureNum - GL_TEXTURE0);
}

uint GlProgram::ProgramID()
{
	return m_nProgramID;
}
