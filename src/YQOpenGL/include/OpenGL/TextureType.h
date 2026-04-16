#pragma once
#include <stdint.h>

namespace YQ
{
	namespace OpenGL
	{
		enum TextureType : uint8_t
		{
			eTEXTURE_2D,
			eDefault = eTEXTURE_2D,
			eTEXTURE_2DARRAY,
			eTEXTURE_2DMULSAMPLE,
			eTEXTURE_BUFFER,
			eTEXTURE_CUBE
		};
	}
}