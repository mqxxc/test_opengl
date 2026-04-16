#pragma once

#include <string>
#include <vector>

namespace YQ
{
	namespace OpenGL
	{
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
			uint32_t ShaderID();


		protected:
			uint32_t m_nShaderID = 0;
			bool m_bValid = false;

			Shader();
			static Shader* CreateVertexShader();
			static Shader* CreateFragmentShader();
			bool CheckError();

			friend class GlProgram;
		};
	}
}