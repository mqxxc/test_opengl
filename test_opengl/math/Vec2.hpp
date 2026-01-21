#pragma once
#include "Vec.hpp"
namespace YQ
{
	template<typename T>
	class Vec2 : public Vec<T>
	{
	public:
		using Vec<T>::Copy;

		Vec2();
		Vec2(const T& x, const T& y);
		template<typename U = T, typename std::enable_if<!std::is_same<U, Vec2<T>>::value, bool>::type = false>
		Vec2(const T& defValue);
		Vec2(const Vec<T>& other);

		T x();
		T y();
		void SetX(const T& value);
		void SetY(const T& value);

	protected:
		using Vec<T>::m_data;
		using Vec<T>::m_nSize;
		void InitDefValue(const T& defValue);
	};
}

#include "Vec2.inl"