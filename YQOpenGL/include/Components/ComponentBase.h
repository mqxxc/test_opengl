#pragma once
#include <string>

namespace YQ
{
	class ComponentBase
	{
	public:
		ComponentBase() = default;
		virtual ~ComponentBase() = default;

		virtual const std::string GetName() const = 0;

	protected:

	};
}
