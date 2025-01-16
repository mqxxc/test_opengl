#pragma once
#include "pch.h"

#include <string>
#include <vector>

class GlProgram;
//着色器类
class Shader
{
public:
	~Shader();

	short LoadFromFile(const std::vector<std::string>& strPath);
	short LoadFromFile(const std::string& strPath);
	short LoadFromString(const std::vector<std::string>& strData);
	short LoadFromString(const std::string& strData);
	bool IsValid();
	uint ShaderID();
	

protected:
	uint m_nShaderID = 0;
	bool m_bValid = false;

	Shader();
	static Shader* CreateVertexShader();
	static Shader* CreateFragmentShader();
	bool CheckError();

	friend class GlProgram;
};
