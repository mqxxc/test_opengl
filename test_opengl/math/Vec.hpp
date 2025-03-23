#pragma once
namespace YQ
{
	template<class T>
	class Vec 
	{
	public:
		Vec();
		template<typename... Args>
		Vec(Args&... args);
		Vec(int size);
		Vec(const Vec& other);
		Vec(Vec&& other);
		virtual ~Vec();

		void Resize(int size);
		int Size() const;
		bool IsEmpty() const;
		const T& At(int nIndex) const;
		bool SetValue(int nIndex, const T& value);
		void Clear();
		void Destroy();
		Vec<T>& Normalization();

		T& operator[](int nIndex);

#ifdef _DEBUG
		void print();
#endif // _DEBUG

	protected:
		T* m_data = nullptr;
		int m_nSize;
	};
};

#include "../Source/Vec.ipp"