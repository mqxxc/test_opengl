#pragma once
#include "pch.h"

#include <vector>
#include <list>
#include <string>

//gl渲染程序
class Shader;
class TextureUnit;
class GlProgram
{
public:
	GlProgram();
	~GlProgram();

	void CreateVertexShader(const std::vector<std::string>& Source);
	void CreateVertexShader(const std::string& Source);
	void CreateVertexShaderFromFile(const std::string& strFile);
	void CreateVertexShaderFromFile(const std::vector<std::string>& strFile);

	void CreateFragmentShader(const std::vector<std::string>& Source);
	void CreateFragmentShader(const std::string& Source);
	void CreateFragmentShaderFromFile(const std::string& strFile);
	void CreateFragmentShaderFromFile(const std::vector<std::string>& strFile);

	bool Complete();
	void SetTextureUnit(TextureUnit* tex, const std::string& varName);
	uint ProgramID();

private:
	uint m_nProgramID = -1;
	std::list<Shader*> m_listShader;
};

