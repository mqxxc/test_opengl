#include "LineRowView.hpp"
namespace YQ
{
	template<typename T>
	LineRowView<T>::LineRowView(T* dataPtr, int nLength)
	{
		m_dataPtr = dataPtr;
		m_nLength = nLength;
	}

	template<typename T>
	LineRowView<T>::~LineRowView()
	{
	}

	template<typename T>
	int LineRowView<T>::Length() const
	{
		return m_nLength;
	}

	template<typename T>
	T& LineRowView<T>::operator[](int index)
	{
		assert(index >= 0 || index < m_nLength);
		return m_dataPtr[index];
	}
}