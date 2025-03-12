#include "Shader.h"

#include "glad/glad.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader()
{
}

Shader::~Shader()
{
    if (m_nShaderID != 0)
    {
        glDeleteShader(m_nShaderID);
    }
}

Shader* Shader::CreateVertexShader()
{
    Shader* obj = new Shader;
    obj->m_nShaderID = glCreateShader(GL_VERTEX_SHADER);
    return obj;
}

Shader* Shader::CreateFragmentShader()
{
    Shader* obj = new Shader;
    obj->m_nShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    return obj;
}

bool Shader::CheckError()
{
    int nCode = GL_FALSE;
    glGetShaderiv(m_nShaderID, GL_COMPILE_STATUS, &nCode);
    if (nCode != GL_TRUE)
    {
        char info[512];
        glGetShaderInfoLog(m_nShaderID, 512, nullptr, info);
        std::cout << "compile Shader error:" << info << std::endl;
        return false;
    }
    return true;
}

short Shader::LoadFromFile(const std::vector<std::string>& strPath)
{
    m_bValid = false;

    if (m_nShaderID == -1)
    {
        return -1;
    }

    int nCount = strPath.size();
    std::vector<std::string> datas(nCount, "");
    for (int i = 0; i < nCount; ++i)
    {
        std::ifstream file;
        file.open(strPath[i], std::ios::in);
        if (!file.is_open())
        {
            return -3;
        }
        std::string value;
        std::string buff;
        while (std::getline(file, buff))
        {
            if (buff.find("$") == -1)
            {
                datas[i].append(buff);
                datas[i].append("\n");
            }
            datas[i].append("\0");
        }
        file.close();
    }

    const char** shaderParts = new const char* [nCount];
    for (int i = 0; i < nCount; ++i)
    {
        shaderParts[i] = datas[i].c_str();
    }

    glShaderSource(m_nShaderID, nCount, shaderParts, nullptr);
    glCompileShader(m_nShaderID);

    delete[] shaderParts;

    if (CheckError())
    {
        m_bValid = true;
        return 0;
    }

    return -2;
}

short Shader::LoadFromFile(const std::string& strPath)
{
    m_bValid = false;

    if (m_nShaderID == -1)
    {
        return -1;
    }

    std::ifstream file;
    file.open(strPath, std::ios::in);
    if (!file.is_open())
    {
        return -3;
    }
    std::string value;
    std::string buff;
    while (std::getline(file, buff))
    {
        if (buff.find("$") == -1)
        {
            value.append(buff);
            value.append("\n");
        }
        value.append("\0");
    }
    file.close();

    const char* data = value.c_str();

    glShaderSource(m_nShaderID, 1, &data, nullptr);
    glCompileShader(m_nShaderID);

    if (CheckError())
    {
        m_bValid = true;
        return 0;
    }
    return -2;
}

short Shader::LoadFromString(const std::vector<std::string>& strData)
{
    if (m_nShaderID == -1)
    {
        return -1;
    }

    int nCount = strData.size();
    char const** buff = new const char* [nCount];

    for (int i = 0; i < nCount; ++i)
    {
        buff[i] = strData.at(i).c_str();
    }

    glShaderSource(m_nShaderID, nCount, buff, nullptr);
    glCompileShader(m_nShaderID);
    delete[] buff;

    if (CheckError())
    {
        m_bValid = true;
        return 0;
    }
    return -2;
}

short Shader::LoadFromString(const std::string& strData)
{
    if (m_nShaderID == -1)
    {
        return -1;
    }
    const char* buff = strData.c_str();
    glShaderSource(m_nShaderID, 1, &buff, nullptr);
    glCompileShader(m_nShaderID);

    if (CheckError())
    {
        m_bValid = true;
        return 0;
    }
    return -2;
}

bool Shader::IsValid()
{
    return m_bValid;
}

uint Shader::ShaderID()
{
    return m_nShaderID;
}
