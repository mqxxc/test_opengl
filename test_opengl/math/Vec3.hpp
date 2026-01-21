#pragma once
#include "Vec2.hpp"

namespace YQ
{
	template<typename T>
	class Vec3 : public Vec2<T>
	{
	public:
		using Vec<T>::Copy;
		using Vec2<T>::x;
		using Vec2<T>::y;
		using Vec2<T>::InitDefValue;
		using Vec<T>::operator*;

		Vec3();
		Vec3(const T& x, const T& y, const T& z);
		template<typename U = T, typename std::enable_if<!std::is_same<U, Vec3<T>>::value, bool>::type = false>
		Vec3(const T& defValue);
		Vec3(const Vec<T>& other);

		T z();
		void SetZ(const T& value);
		template<typename U = T, typename std::enable_if<std::is_same<U, Vec3<T>>::value, bool>::type = true>
		Vec3<T> operator*(const Vec3<T>& vec) const;

	protected:
		using Vec<T>::m_data;
		using Vec<T>::m_nSize;
	};
}

#include "Vec3.inl"