#pragma once
#include "Vec.hpp"
namespace YQ
{
	template<typename T>
	class Vec2 : public Vec<T>
	{
	public:
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
		using Vec<T>::Copy;
		void InitDefValue(const T& defValue);
	};

	//////////////////////////////////////
	template<typename T>
	inline Vec2<T>::Vec2()
		: Vec<T>(2)
	{
	}

	template<typename T>
	inline Vec2<T>::Vec2(const T& x, const T& y)
		: Vec<T>(x, y)
	{
	}

	template<typename T>
	template<typename U, typename std::enable_if<!std::is_same<U, Vec2<T>>::value, bool>::type>
	inline Vec2<T>::Vec2(const T& defValue)
		: Vec2()
	{
		InitDefValue(defValue);
	}

	template<typename T>
	inline Vec2<T>::Vec2(const Vec<T>& other)
		: Vec2<T>()
	{
		Copy(other);
	}

	template<typename T>
	inline T Vec2<T>::x()
	{
		return m_data[0];
	}

	template<typename T>
	inline T Vec2<T>::y()
	{
		return m_data[1];
	}

	template<typename T>
	inline void Vec2<T>::SetX(const T& value)
	{
		m_data[0] = value;
	}

	template<typename T>
	inline void Vec2<T>::SetY(const T& value)
	{
		m_data[1] = value;
	}

	template<typename T>
	inline void Vec2<T>::InitDefValue(const T& defValue)
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] = defValue;
		}
	}
}