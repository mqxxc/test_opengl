#pragma once
#include "../YQMath_global.h"

namespace YQ
{
	template<typename T>
	class YQMath_EXPORT LineRowView
	{
	public:
		LineRowView(T* dataPtr = nullptr, int nLength = 0);
		~LineRowView();
		int Length() const;

		T& operator[](int index);

	protected:
		T* m_dataPtr = nullptr;
		int m_nLength = 0;
	};
}

#include "Internal/LineRowView.inl"