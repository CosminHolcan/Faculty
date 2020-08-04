#include "Exceptions.h"

RepositoryException::RepositoryException(std::string messageException) : message{ messageException }
{}

std::string RepositoryException::getMessage() const
{
	return this->message;
}

ValidatorException::ValidatorException(std::string messageException)
{
	this->message = messageException;
}

std::string ValidatorException::getMessage() const
{
	return this->message;
}