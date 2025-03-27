#pragma once
#include "Vec.hpp"
#include <assert.h>

namespace YQ
{
	template<typename T, int nSize>
	Vec<T, nSize>::Vec()
	{
		m_nSize = nSize;
		if (m_nSize > 0)
		{
			m_data = new T[m_nSize];
		}
	}

	template<typename T, int nSize>
	template<typename ...Args>
	Vec<T, nSize>::Vec(Args && ...args)
		: Vec()
	{
		int i = 0;
		((m_data[i++] = std::forward<Args>(args)), ...);
	}

	template<typename T, int nSize>
	Vec<T, nSize>::Vec(const T& defValue)
		: Vec()
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] = defValue;
		}
	}

	template<typename T, int nSize>
	Vec<T, nSize>::Vec(const Vec& other)
		: Vec()
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] = other.m_data[i];
		}
	}

	template<typename T, int nSize>
	Vec<T, nSize>::Vec(Vec&& other)
	{
		Destroy();
		m_data = other.m_data;
		m_nSize = other.m_nSize;

		other.m_data = nullptr;
		other.m_nSize = 0;
	}

	template<typename T, int nSize>
	Vec<T, nSize>::~Vec()
	{
		Destroy();
	}

	template<typename T, int nSize>
	int Vec<T, nSize>::Size() const
	{
		return m_nSize;
	}

	template<typename T, int nSize>
	bool Vec<T, nSize>::IsEmpty() const
	{
		return m_nSize == 0;
	}

	template<typename T, int nSize>
	const T& Vec<T, nSize>::At(int nIndex) const
	{
		if (m_data == nullptr || nIndex < 0 || nIndex >= m_nSize)
		{
			return T();
		}

		return m_data[nIndex];
	}

	template<typename T, int nSize>
	bool Vec<T, nSize>::SetValue(int nIndex, const T& value)
	{
		if (m_data == nullptr || nIndex < 0 || nIndex >= m_nSize)
		{
			return false;
		}

		m_data[nIndex] = value;
		return true;
	}

	template<typename T, int nSize>
	void Vec<T, nSize>::Clear()
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] = T();
		}
	}

	template<typename T, int nSize>
	void Vec<T, nSize>::Destroy()
	{
		if (m_data != nullptr)
		{
			delete m_data;
			m_data = nullptr;
		}

		m_nSize = 0;
	}

	template<typename T, int nSize>
	Vec<T, nSize>& Vec<T, nSize>::Normalization()
	{
		double length = 0;
		for (int i = 0; i < m_nSize; ++i)
		{
			length += m_data[i] * m_data[i];
		}

		if (length != 0)
		{
			length = sqrt(length);
			for (int i = 0; i < m_nSize; ++i)
			{
				m_data[i] /= static_cast<T>(length);
			}
		}
		return (*this);
	}

	template<typename T, int nSize>
	const T* const Vec<T, nSize>::Data() const
	{
		return m_data;
	}

	template<typename T, int nSize>
	T& Vec<T, nSize>::operator[](int nIndex)
	{
		assert(m_data != nullptr && (nIndex >= 0 && nIndex < m_nSize));

		return m_data[nIndex];
	}

	template<typename T, int nSize>
	template<typename U, typename std::enable_if<!std::is_same<U, Vec<T, nSize>>::value, bool>::type>
	inline Vec<T, nSize> Vec<T, nSize>::operator*(const U& value) const
	{
		Vec<T, nSize> res(*this);
		for (int i = 0; i < m_nSize; ++i)
		{
			res.m_data[i] *= value;
		}
		return res;
	}

	template<typename T, int nSize>
	template<typename U, typename std::enable_if<std::is_same<U, Vec<T, nSize>>::value, bool>::type>
	inline Vec<T, nSize> Vec<T, nSize>::operator*(const Vec<T, nSize>& vec) const
	{
		Vec<T, nSize> temp;
		for (int i = 0; i < temp.m_nSize; ++i)
		{
			temp.m_data[i] *= vec.m_data[i];
		}
		return temp;
	}
	
	template<typename T, int nSize>
	inline Vec<T, nSize> Vec<T, nSize>::operator+(const Vec<T, nSize>& vec) const
	{
		Vec<T, nSize> res;
		for (int i = 0; i < m_nSize; ++i)
		{
			res[i] = m_data[i] + vec.m_data[i];
		}
		return res;
	}

	template<typename T, int nSize>
	Vec<T, nSize>& Vec<T, nSize>::operator+=(const Vec<T, nSize>& vec)
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] += vec.At(i);
		}
		return (*this);
	}

	template<typename T, int nSize>
	inline Vec<T, nSize> Vec<T, nSize>::operator-(const Vec<T, nSize>& vec) const
	{
		Vec<T, nSize> res;
		for (int i = 0; i < m_nSize; ++i)
		{
			res[i] = m_data[i] - vec.m_data[i];
		}
		return res;
	}

	template<typename T, int nSize>
	Vec<T, nSize>& Vec<T, nSize>::operator-=(const Vec<T, nSize>& vec)
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] -= vec.At(i);
		}
		return (*this);
	}

	template<typename T, int nSize>
	void Vec<T, nSize>::operator=(const Vec<T, nSize>& vec)
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_data[i] = vec.At(i);
		}
	}
}

#ifdef _DEBUG
#include <iostream>
template<typename T, int nSize>
void YQ::Vec<T, nSize>::print() const
{
	for (int i = 0; i < m_nSize; ++i)
	{
		std::cout << m_data[i] << "   ";
	}
	std::cout << std::endl << std::endl;
}
#endif // _DEBUG