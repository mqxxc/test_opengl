#pragma once
#include "glad/glad.h"
#include "TextureType.h"

#include "glad/glad.h"

#include <string>
#include <string_view>

//纹理单元
namespace YQ
{
	namespace OpenGL
	{
		class TextureUnit
		{
		public:
			enum Around : uint32_t
			{
				eREPEAT = GL_REPEAT,
				eMirror = GL_MIRRORED_REPEAT,
				eStretching = GL_CLAMP_TO_EDGE,
				eBackgroundFill = GL_CLAMP_TO_BORDER
			};

			enum Zoom : uint32_t
			{
				eNEAREST = GL_NEAREST,
				eLINEAR = GL_LINEAR
			};

			TextureUnit(TextureType type, const std::string_view objectName = std::string_view{});
			~TextureUnit();

			bool LoadImg(const std::string& imgPath, bool reverseY = false);	//加载图像到纹理单元
			void SetRowAround(Around around);		//设置行边缘扩展
			void SetColumnAround(Around around);	//设置列边缘扩展
			void SetAmplifyStrategy(Zoom zoom);		//设置放大策略
			void SetShrinkStrategy(Zoom zoom);		//设置缩小策略
			void CreateGenerateMipmap();			//创建Mip映射表
			bool Build(uint32_t nGlTexture = 0);	//当没有传入默认纹理单元编号时需手动绑定对应纹理单元编号
			uint32_t TextureNum();

		protected:
			uint32_t m_nTextureID;			//纹理单元ID
			std::string m_strObjName;		//对象名称

			uint32_t m_nGlTextureNum;		//gl纹理单元编号
			
			static uint32_t m_gTextureID;	//当前绑定的纹理单元

			void SetParameteri(uint32_t type, uint32_t around);

			friend class GlProgram;
		};
	}
}