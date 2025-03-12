#pragma once
#include "pch.h"

#include <vector>
#include <list>
#include <string>
#include "glm/glm.hpp"

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
    void SetUniform(const std::string& name, const glm::vec2& value) const;
    void SetUniform(const std::string& name, float x, float y) const;
    void SetUniform(const std::string& name, const glm::vec3& value) const;
    void SetUniform(const std::string& name, float x, float y, float z) const;
    void SetUniform(const std::string& name, const glm::vec4& value) const;
    void SetUniform(const std::string& name, float x, float y, float z, float w) const;
    void SetUniform(const std::string& name, const glm::mat2& mat) const;
    void SetUniform(const std::string& name, const glm::mat3& mat) const;
    void SetUniform(const std::string& name, const glm::mat4& mat) const;

private:
	uint m_nProgramID = -1;
	Shader* m_listShader[2];

	void ClearShader();
};

