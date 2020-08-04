#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Victim
{
private:
	std::string name;
	std::string placeOfOrigin;
	int age;
	std::string photograph;

public:
	Victim();
	//constructor without parameters

	Victim(const std::string& name, const std::string& placeoforigin, int age, const std::string& photograph);
	// constructor with parameters


	std::string getName() const {
		return name;
	}
	std::string getPlaceOfOrigin() const {
		return placeOfOrigin;
	}
	int getAge() const {
		return age;
	}
	std::string getPhotograph() const {
		return photograph;
	}

	bool operator ==(const Victim& victim) const
		//overloading the operator ==
	{
		return this->name == victim.getName();
	}

	friend std::istream& operator>>(std::istream& inputStream, Victim& victim);
	friend std::ostream& operator<<(std::ostream& outputStream, Victim& victim);
};