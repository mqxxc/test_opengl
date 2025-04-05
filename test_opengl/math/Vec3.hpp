#pragma once
#include "Vec2.hpp"

namespace YQ
{
	template<typename T>
	class Vec3 : public Vec2<T>
	{
	public:
		Vec3();
		Vec3(const T& x, const T& y, const T& z);
		template<typename U = T, typename std::enable_if<!std::is_same<U, Vec<T>>::value, bool>::type = false>
		Vec3(const U& defValue);
		Vec3(const Vec<T>& other);

		T z();
		void SetZ(const T& value);

	protected:
		using Vec<T>::m_data;
		using Vec<T>::m_nSize;
	};
	//////////////////////////////////////////////
	template<typename T>
	inline Vec3<T>::Vec3()
	{
		m_nSize = 3;
		m_data = new T[m_nSize];
	}
	template<typename T>
	inline Vec3<T>::Vec3(const T& x, const T& y, const T& z)
		: Vec3<T>()
	{
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
	}

	template<typename T>
	template<typename U, typename std::enable_if<!std::is_same<U, Vec<T>>::value, bool>::type>
	inline Vec3<T>::Vec3(const U& defValue)
		: Vec3<T>()
	{
		InitDefValue(defValue);
	}
	template<typename T>
	inline Vec3<T>::Vec3(const Vec<T>& other)
		: Vec3<T>()
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] = other.At(i);
		}
	}

	template<typename T>
	inline T Vec3<T>::z()
	{
		return m_data[2];
	}

	template<typename T>
	inline void Vec3<T>::SetZ(const T& value)
	{
		m_data[2] = value;
	}
}