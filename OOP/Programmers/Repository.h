#pragma once
#include "Domain.h"
#include <algorithm>
#include <exception>
#include <fstream>

using namespace std;

template <typename T>
class Repository
{
private:
	string file;
public:
	Repository(string file) : file(file) {}
	void add(T elem);
	void update(T elem);
	void exist(T elem);
	void remove(T elem);
	vector<T> getAll();
	void writeToFile(vector<T> elements);
};

template<typename T>
inline void Repository<T>::add(T elem)
{
	vector<T> elements = this->getAll();
	for (auto item : elements)
	{
		if (item == elem)
			return;
	}
	elements.push_back(elem);
	this->writeToFile(elements);

}

template<typename T>
inline void Repository<T>::update(T elem)
{
	vector<T> elements = this->getAll();
	if (std::find(elements.begin(), elements.end(), elem) != elements.end())
	{
		elements.erase(std::find(elements.begin(), elements.end(), elem));
		elements.push_back(elem);
	}
	this->writeToFile(elements);
}

template<typename T>
inline void Repository<T>::exist(T elem)
{
	if (std::find(elements.begin(), elements.end(), elem) != elements.end())
	{
		return true;
	}
	return false;
}

template<typename T>
inline void Repository<T>::remove(T elem)
{
	vector<T> elements = this->getAll();
	if (std::find(elements.begin(), elements.end(), elem) != elements.end())
	{
		elements.erase(std::find(elements.begin(), elements.end(), elem));
	}
	this->writeToFile(elements);
}

template<typename T>
inline vector<T> Repository<T>::getAll()
{
	ifstream fd{ this->file };
	vector<T> elements;
	T elem;
	while (fd >> elem)
	{
		elements.push_back(elem);
	}
	fd.close();
	return elements;
}

template<typename T>
inline void Repository<T>::writeToFile(vector<T> elements)
{
	ofstream fd(this->file);
	for (auto elem : elements)
	{
		fd << elem << '\n';
	}
	fd.close();

}
