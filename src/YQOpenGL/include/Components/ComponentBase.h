#pragma once
#include "../YQOpenGL_global.h"

#include <string>

namespace YQ
{
	class YQOpenGL_EXPORT ComponentBase
	{
	public:
		ComponentBase() = default;
		virtual ~ComponentBase() = default;

		virtual const std::string GetName() const = 0;

	protected:

	};
}
