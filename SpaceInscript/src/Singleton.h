#pragma once


/* Base class for singleton classes
*/
template <typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		static T* instance = nullptr;
		if (!instance)
		{
			instance = new T();
		}

		return instance;
	}


	//Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;


};

