#include "Service.h"

using namespace std;

vector<Issue> Service::getAllIssuesSorted()
{
	vector<Issue> toReturn = this->issues.getAll();
	std::sort(toReturn.begin(), toReturn.end(), [](Issue issue1, Issue issue2)
		{ if (issue1.getStatus() == issue2.getStatus())
		return issue1.getDescription() <= issue2.getDescription();
		else
		return issue1.getStatus() <= issue2.getStatus();
		});
	return toReturn;
}

vector<User> Service::getAllUsers()
{
	return this->users.getAll();
}

void Service::addIssue(string description, string status, string reporter, string solver)
{
	Issue issue(description, status, reporter, solver);
	this->issues.add(issue);
	this->notify();
}

void Service::removeIssue(string description)
{
	Issue issue(description, "", "", "");
	this->issues.remove(issue);
	this->notify();
}

void Service::updateIssue(string description, string status, string reporter, string solver)
{
	Issue issue(description, status, reporter, solver);
	this->issues.update(issue);
	this->notify();
}
