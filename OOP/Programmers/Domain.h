#pragma once
#include <vector>
#include <string>
#include <ostream>
#include <sstream>

using namespace std;

class User
{
private :
	string name;
	string type;
public :
	User(string name, string type) : name(name), type(type) {}
	User() : name(""), type("") {}
	string getName();
	string getType();
	string print();
	bool operator==(const User& other);
	friend std::istream& operator>>(std::istream& inputStream, User& user);
	friend std::ostream& operator<<(std::ostream& out, User& user);
};

class Issue
{
private :
	string description;
	string status;
	string reporter;
	string solver;
public :
	Issue(string description, string status, string reporter, string solver) : description(description), status(status), reporter(reporter),
		solver(solver) {}
	Issue() : description(""), status(""), reporter(""), solver("") {}
	string getDescription();
	string getStatus();
	string getReporter();
	string getSolver();
	string print();
	bool operator==(const Issue& other);
	friend std::istream& operator>>(std::istream& inputStream, Issue& issue);
	friend std::ostream& operator<<(std::ostream& out, Issue& issue);
};