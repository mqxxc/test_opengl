#pragma once
#include <type_traits>
namespace YQ
{
	template<typename T, int nSize>
	class Vec 
	{
	public:
		Vec();
		template<typename... Args>
		explicit Vec(Args&&... args);
		Vec(const T& defValue);
		Vec(const Vec& other);
		Vec(Vec&& other);
		virtual ~Vec();

		int Size() const;
		bool IsEmpty() const;
		const T& At(int nIndex) const;
		bool SetValue(int nIndex, const T& value);
		void Clear();
		void Destroy();
		Vec<T, nSize>& Normalization();
		const T* const Data() const;

		T& operator[](int nIndex);

		template<typename U = T, typename std::enable_if<!std::is_same<U, Vec<T, nSize>>::value, bool>::type = false>
		Vec<T, nSize> operator*(const U& vec) const;
		template<typename U = T, typename std::enable_if<std::is_same<U, Vec<T, nSize>>::value, bool>::type = true>
		Vec<T, nSize> operator*(const Vec<T, nSize>& vec) const;
		Vec<T, nSize> operator+(const Vec<T, nSize>& vec) const;
		Vec<T, nSize>& operator+=(const Vec<T, nSize>& vec);
		Vec<T, nSize> operator-(const Vec<T, nSize>& vec) const;
		Vec<T, nSize>& operator-=(const Vec<T, nSize>& vec);
		void operator=(const Vec<T, nSize>& vec);

#ifdef _DEBUG
		void print() const;
#endif // _DEBUG

	protected:
		T* m_data = nullptr;
		int m_nSize;
	};
};

#include "../Source/Vec.ipp"