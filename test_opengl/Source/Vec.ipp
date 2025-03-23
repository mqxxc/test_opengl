#pragma once
#include "Vec.hpp"
#include <assert.h>

template<class T>
YQ::Vec<T>::Vec()
{
	m_nSize = 0;
}

template<class T>
template<typename ...Args>
YQ::Vec<T>::Vec(Args & ...args)
{
	Resize(sizeof...(args));
	int i = 0;
	((m_data[i++] = std::forward<Args>(args)), ...);
}

template<class T>
YQ::Vec<T>::Vec(int size)
{
	Resize(size);
}

template<class T>
YQ::Vec<T>::Vec(const Vec& other)
{
	Resize(other.m_nSize);

	for (int i = 0; i < m_nSize; ++i)
	{
		m_data[i] = other.m_data[i];
	}
}

template<class T>
YQ::Vec<T>::Vec(Vec&& other)
{
	Destroy();
	m_data = other.m_datal;
	m_nSize = other.m_nSize;

	other.m_datal = nullptr;
	other.m_nSize = 0;
}

template<class T>
YQ::Vec<T>::~Vec()
{
	Destroy();
}

template<class T>
void YQ::Vec<T>::Resize(int size)
{
	if (size <= 0)
	{
		return;
	}

	Destroy();

	m_nSize = size;

	m_data = new T[size];
}

template<class T>
int YQ::Vec<T>::Size() const
{
	return m_nSize;
}

template<class T>
bool YQ::Vec<T>::IsEmpty() const
{
	return m_nSize == 0;
}

template<class T>
const T& YQ::Vec<T>::At(int nIndex) const
{
	if (m_data == nullptr || nIndex < 0 || nIndex >= m_nSize)
	{
		return T();
	}

	return m_data[nIndex];
}

template<class T>
bool YQ::Vec<T>::SetValue(int nIndex, const T& value)
{
	if (m_data == nullptr || nIndex < 0 || nIndex >= m_nSize)
	{
		return false;
	}

	m_data[nIndex] = value;
	return true;
}

template<class T>
void YQ::Vec<T>::Clear()
{
	for (int i = 0; i < m_nSize; ++i)
	{
		m_data[i] = T();
	}
}

template<class T>
void YQ::Vec<T>::Destroy()
{
	if (m_data != nullptr)
	{
		delete m_data;
		m_data = nullptr;
	}

	m_nSize = 0;
}

template<class T>
YQ::Vec<T>& YQ::Vec<T>::Normalization()
{
	double length = 0;
	for (int i = 0; i < m_nSize; ++i)
	{
		length += m_data[i] * m_data[i];
	}
	assert(length != 0);
	length = sqrt(length);
	for (int i = 0; i < m_nSize; ++i)
	{
		m_data[i] /= static_cast<T>(length);
	}
	return (*this);
}

template<class T>
T& YQ::Vec<T>::operator[](int nIndex)
{
	assert(m_data != nullptr &&(nIndex > 0 && nIndex < m_nSize));

	return m_data[nIndex];
}

#ifdef _DEBUG
#include <iostream>
template<class T>
void YQ::Vec<T>::print()
{
	for (int i = 0; i < m_nSize; ++i)
	{
		std::cout << m_data[i] << "   ";
	}
	std::cout << std::endl;
}
#endif // _DEBUG


