#include "Domain.h"

Victim::Victim() : name(""), placeOfOrigin(""), age(0), photograph("") {}

Victim::Victim(const std::string& name, const  std::string& placeOfOrigin, int age, const std::string& photograph)
{
	this->name = name;
	this->placeOfOrigin = placeOfOrigin;
	this->age = age;
	this->photograph = photograph;
}



std::istream& operator>>(std::istream& inputStream, Victim& victim)
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
	victim.name = parameters[0];
	victim.placeOfOrigin = parameters[1];
	victim.age = stoi(parameters[2]);
	victim.photograph = parameters[3];
	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, Victim& victim)
{
	std::string name = victim.getName();
	std::string place = victim.getPlaceOfOrigin();
	std::string age = std::to_string(victim.getAge());
	std::string photograph = victim.getPhotograph();
	outputStream << name << ',' << place << ',' << age << ',' << photograph << '\n';
	return outputStream;
}