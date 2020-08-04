#include "Domain.h"

string User::getName()
{
	return this->name;
}

string User::getType()
{
	return this->type;
}

string User::print()
{
	return this->name + " - " + this->type;
}

bool User::operator==(const User& other)
{
	return this->name == other.name;
}

std::istream& operator>>(std::istream& inputStream, User& user)
{
	std::string line{};
	getline(inputStream, line);
	std::vector<std::string> parameters;
	stringstream streamToGetParameters(line);
	string parameter;
	while (getline(streamToGetParameters, parameter, ','))
		parameters.push_back(parameter);
	if (parameters.size() == 0)
		return inputStream;
	user.name = parameters[0];
	user.type = parameters[1];
	return inputStream;
}

std::ostream& operator<<(std::ostream& out, User& user)
{
	string s = user.getName() + "," + user.getType();
	out << s;
	return out;
}


string Issue::getDescription()
{
	return this->description;
}

string Issue::getStatus()
{
	return this->status;
}

string Issue::getReporter()
{
	return this->reporter;
}

string Issue::getSolver()
{
	return this->solver;
}

string Issue::print()
{
	return this->description + " | " + this->status + " | " + this->reporter + " | " + this->solver;
}

bool Issue::operator==(const Issue& other)
{
	return this->description == other.description;
}

std::istream& operator>>(std::istream& inputStream, Issue& issue)
{
	std::string line{};
	getline(inputStream, line);
	std::vector<std::string> parameters;
	stringstream streamToGetParameters(line);
	string parameter;
	while (getline(streamToGetParameters, parameter, ','))
		parameters.push_back(parameter);
	if (parameters.size() == 0)
		return inputStream;
	issue.description = parameters[0];
	issue.status = parameters[1];
	issue.reporter = parameters[2];
	issue.solver = parameters[3];
	return inputStream;
}

std::ostream& operator<<(std::ostream& out, Issue& issue)
{
	string s = issue.description + "," + issue.status + "," + issue.reporter + "," + issue.solver;
	out << s;
	return out;
}