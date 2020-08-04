#pragma once
#include "Repository.h"
#include "Observer.h"
using namespace std;

class Service : public Subject
{
private :
	Repository<User> users;
	Repository<Issue> issues;
public :
	Service(Repository<User> users, Repository<Issue> issues) : users(users), issues(issues) {}
	vector<Issue> getAllIssuesSorted();
	vector<User> getAllUsers();
	void addIssue(string description, string status, string reporter, string solver);
	void removeIssue(string description);
	void updateIssue(string description, string status, string reporter, string solver);
};