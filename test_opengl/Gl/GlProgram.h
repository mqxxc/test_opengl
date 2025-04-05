#pragma once
#include "pch.h"

#include <vector>
#include <list>
#include <string>
#include "Matrix.hpp"
#include "Vec.hpp"

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

	void Use();
	uint ProgramID();
	bool Complete();
	void SetTextureUnit(TextureUnit* tex, const std::string& varName);

	void SetUniform(const std::string& name, bool value) const;
	void SetUniform(const std::string& name, int value) const;
	void SetUniform(const std::string& name, float value) const;
	
	void SetUniform(const std::string& name, float x, float y) const;
	void SetUniform(const std::string& name, float x, float y, float z) const;
	void SetUniform(const std::string& name, float x, float y, float z, float w) const;
	void SetUniform(const std::string& name, const YQ::Vec<float>& vec);
	void SetUniform(const std::string& name, const YQ::Matrix<float, 2, 2>& value) const;
	void SetUniform(const std::string& name, const YQ::Matrix<float, 3, 3>& value) const;
	void SetUniform(const std::string& name, const YQ::Matrix<float, 4, 4>& value) const;

private:
	uint m_nProgramID = -1;
	Shader* m_listShader[2] = {nullptr, nullptr};

	void ClearShader();
};

