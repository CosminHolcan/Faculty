#pragma once
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Task
{
private :
	string description;
	int duration;
	int priority;
public :
	Task();
	Task(string description, int duration, int priority);
	string getDescription();
	int getDuration();
	int getPriority();
	friend std::istream& operator>>(std::istream& inputStream, Task& task);
};