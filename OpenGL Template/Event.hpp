#pragma once
#include <list>

template<typename T>
class Event 
{
protected:
	std::list<T> Subscribers;

public:

	void Subscribe(T listener)
	{
		Subscribers.push_back(listener);
	}
};