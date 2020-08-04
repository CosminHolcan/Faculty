#include "Domain.h"

using namespace std;

Task::Task() : description(""), duration(0), priority(0)
{
}

Task::Task(string description, int duration, int priority) : description(description), duration(duration), priority(priority)
{
}

string Task::getDescription()
{
	return this->description;
}

int Task::getDuration()
{
	return this->duration;
}

int Task::getPriority()
{
	return this->priority;
}

std::istream& operator>>(std::istream& inputStream, Task& task)
{
	std::string line{};
	getline(inputStream, line);
	std::vector<std::string> parameters;
	stringstream streamToGetParameters(line);
	string parameter;
	while (getline(streamToGetParameters, parameter, '|'))
	{
		parameters.push_back(parameter);
	}
	if (parameters.size() == 0)
		return inputStream;
	parameters[0].erase(parameters[0].end());
	parameters[1].erase(parameters[1].begin());
	parameters[1].erase(parameters[1].end()-1);
	parameters[2].erase(parameters[2].begin());
	task.description = parameters[0];
	task.duration = stoi(parameters[1]);
	task.priority = stoi(parameters[2]);
	return inputStream;
}