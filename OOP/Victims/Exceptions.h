#pragma once
#include <string>

class RepositoryException
{
private:
	std::string message;
public:
	RepositoryException(std::string messageException);
	std::string getMessage() const;
};

class ValidatorException
{
private:
	std::string message;
public:
	ValidatorException(std::string messageException);
	std::string getMessage() const;
};

