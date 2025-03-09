#pragma once
#include "pch.h"
#include "glad/glad.h"

#include <string>
//纹理单元
class TextureUnit
{
public:
	enum Around : uint
	{
		eREPEAT = GL_REPEAT,
		eMirror = GL_MIRRORED_REPEAT,
		eStretching = GL_CLAMP_TO_EDGE,
		eBackgroundFill = GL_CLAMP_TO_BORDER
	};

	enum Zoom : uint
	{
		eNEAREST = GL_NEAREST,
		eLINEAR = GL_LINEAR
	};

	TextureUnit(uint nGlTexture);
	~TextureUnit();

	bool LoadImg(const std::string& imgPath);
	void SetRowAround(Around around);
	void SetColumnAround(Around around);
	void SetAmplifyStrategy(Zoom zoom);
	void SetShrinkStrategy(Zoom zoom);
	void CreateGenerateMipmap();

protected:
	uint m_nGlTextureNum;
	uint m_nTextureID;
	static uint m_gTextureID;

	void SetParameteri(uint type, uint around);

	friend class GlProgram;
};

