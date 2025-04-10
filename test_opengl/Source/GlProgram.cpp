#include <iostream>

#include "GlProgram.h"
#include "Shader.h"
#include "TextureUnit.h"

#include "glad/glad.h"

GlProgram::GlProgram()
{
	m_nProgramID = glCreateProgram();
}

GlProgram::~GlProgram()
{
	ClearShader();

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
		m_listShader[0] = pShader;
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
		m_listShader[0] = pShader;
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
		m_listShader[0] = pShader;
	}
}

void GlProgram::CreateVertexShaderFromFile(const std::vector<std::string>& strFile)
{
	Shader* pShader = Shader::CreateVertexShader();
	if (pShader->LoadFromFile(strFile) != 0)
	{
		std::cout << "VertexShader create error" << std::endl;
	}
	else
	{
		m_listShader[0] = pShader;
	}
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
		m_listShader[1] = pShader;
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
		m_listShader[1] = pShader;
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
		m_listShader[1] = pShader;
	}
}

void GlProgram::CreateFragmentShaderFromFile(const std::vector<std::string>& strFile)
{
	Shader* pShader = Shader::CreateFragmentShader();
	if (pShader->LoadFromFile(strFile) != 0)
	{
		std::cout << "FragmentShader create error" << std::endl;
	}
	else
	{
		m_listShader[1] = pShader;
	}
}

bool GlProgram::Complete()
{
	if (m_nProgramID == -1)
	{
		return false;
	}

	for (auto it : m_listShader)
	{
		if (it != nullptr)
		{
			glAttachShader(m_nProgramID, it->ShaderID());
		}
		else
		{
			throw "Shader exit nullptr";
		}
	}
	glLinkProgram(m_nProgramID);

	ClearShader();

	return true;
}

void GlProgram::SetTextureUnit(TextureUnit* tex, const std::string& varName)
{
	glUniform1i(glGetUniformLocation(m_nProgramID, varName.c_str()), tex->TextureNum());	
}

void GlProgram::SetUniform(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_nProgramID, name.c_str()), (int)value);
}

void GlProgram::SetUniform(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_nProgramID, name.c_str()), value);
}

void GlProgram::SetUniform(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_nProgramID, name.c_str()), value);
}

void GlProgram::SetUniform(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_nProgramID, name.c_str()), x, y);
}

void GlProgram::SetUniform(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_nProgramID, name.c_str()), x, y, z);
}

void GlProgram::SetUniform(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_nProgramID, name.c_str()), x, y, z, w);
}

void GlProgram::SetUniform(const std::string& name, const YQ::Vec<float>& vec)
{
	switch (vec.Size())
	{
	case 2:
		glUniform2fv(glGetUniformLocation(m_nProgramID, name.c_str()), 1, vec.Data());
		break;
	case 3:
		glUniform3fv(glGetUniformLocation(m_nProgramID, name.c_str()), 1, vec.Data());
		break;
	case 4:
		glUniform4fv(glGetUniformLocation(m_nProgramID, name.c_str()), 1, vec.Data());
		break;
	default:
		break;
	}
}

void GlProgram::SetUniform(const std::string& name, const YQ::Matrix<float, 2, 2>& value) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_nProgramID, name.c_str()), 1, GL_FALSE, value.Data());
}

void GlProgram::SetUniform(const std::string& name, const YQ::Matrix<float, 3, 3>& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_nProgramID, name.c_str()), 1, GL_FALSE, value.Data());
}

void GlProgram::SetUniform(const std::string& name, const YQ::Matrix<float, 4, 4>& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_nProgramID, name.c_str()), 1, GL_FALSE, value.Data());
}

void GlProgram::Use()
{
	glUseProgram(m_nProgramID);
}

uint GlProgram::ProgramID()
{
	return m_nProgramID;
}

void GlProgram::ClearShader()
{
	for (int i = 0; i < 2; ++i)
	{
		delete m_listShader[i];
		m_listShader[i] = nullptr;
	}
}
