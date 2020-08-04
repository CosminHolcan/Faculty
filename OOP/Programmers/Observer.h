#pragma once
#include <vector>
#include <algorithm>

using namespace std;

class Observer
{
public:
	virtual void update() = 0;
	virtual ~Observer() {}
};

class Subject
{
protected:
	vector<Observer*> observers;
public:
	void addObserver(Observer* observer)
	{
		this->observers.push_back(observer);
	}
	void removeObserver(Observer* observer)
	{
		auto position = std::find(this->observers.begin(), this->observers.end(), observer);
		if (position != this->observers.end())
		{
			this->observers.erase(position);
		}
	}
	void notify()
	{
		for (auto observer : this->observers)
			observer->update();
	}
};