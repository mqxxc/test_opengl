#pragma once
#include "VertexBuffer.h"
namespace YQ
{
	namespace OpenGL
	{
		class StaticVertexBuffer : public VertexBuffer
		{
		public:
			StaticVertexBuffer(GLsizei nSize = 0);
			~StaticVertexBuffer() noexcept = default;

			virtual void CreateVBO(GLsizei nGroupLength) override;
			bool wirteData(const float* dataPtr, size_t length);
		};
	}
}
