#include "Repository.h"
#include <fstream>
#include <algorithm>
#include <iostream>

Repository::Repository(string nameOfFile) : fileName{nameOfFile}
{
}

vector<Task> Repository::readFromFile()
{
	ifstream file(this->fileName);
	Task task;
	vector<Task> tasks;
	while (file >> task)
		tasks.push_back(task);
	std::sort(tasks.begin(), tasks.end(), [](Task task1, Task task2) { return task1.getPriority() < task2.getPriority(); });
	return tasks;
}

int Repository::totalDuration(int priority)
{
	int result = 0;
	vector<Task> tasks = this->readFromFile();
	for (Task task : tasks)
	{
		if (task.getPriority() == priority)
			result += task.getDuration();
	}
	return result;
}
