#pragma once

template <typename T>
class SingletonBase //알고리즘 디자인패턴
{
public:
	static void Create()
	{
		if (instance == nullptr)
			instance = new T();
	}

	static void Delete()
	{
		delete instance;
		instance = nullptr;
	}

	static T* Get()
	{
		return instance;
	}

protected:
	static T* instance;
};

template<typename T> //뭐든지 통과해주겠다? = 빈 공간
T* SingletonBase<T>::instance = nullptr;