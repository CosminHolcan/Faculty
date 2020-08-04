#pragma once
#include "Domain.h"

using namespace std;

class Repository
{
private :
	std::string fileName;
public :
	Repository(string nameOfFile);
	vector<Task> readFromFile();
	int totalDuration(int priority);
};