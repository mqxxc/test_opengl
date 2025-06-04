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
	TextureUnit();
	~TextureUnit();

	bool LoadImg(const std::string& imgPath, bool reverseY = false);	//加载图像到纹理单元
	void SetRowAround(Around around);		//设置行边缘扩展
	void SetColumnAround(Around around);	//设置列边缘扩展
	void SetAmplifyStrategy(Zoom zoom);		//设置放大策略
	void SetShrinkStrategy(Zoom zoom);		//设置缩小策略
	void CreateGenerateMipmap();			//创建Mip映射表
	bool Build(uint nGlTexture = 0);		//当没有传入默认纹理单元编号时需手动绑定对应纹理单元编号
	uint TextureNum();						

protected:
	uint m_nGlTextureNum;		//gl纹理单元编号
	uint m_nTextureID;			//纹理单元ID
	static uint m_gTextureID;	//当前绑定的纹理单元

	void SetParameteri(uint type, uint around);

	friend class GlProgram;
};

