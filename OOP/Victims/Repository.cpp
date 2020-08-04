#include "Repository.h"


bool InMemoryRepository::repositoryAddVictim(const Victim& victim)
{
	if (std::find(this->victims.begin(), this->victims.end(), victim) == this->victims.end())
	{
		this->victims.push_back(victim);
		return true;
	}
	else
		throw RepositoryException("This victim is already in repository !");
}

bool InMemoryRepository::repositoryDeleteVictim(const Victim& victim)
{
	if (std::find(this->victims.begin(), this->victims.end(), victim) != this->victims.end())
	{
		this->victims.erase(std::remove(this->victims.begin(), this->victims.end(), victim), this->victims.end());
		return true;
	}
	else
		throw RepositoryException("This victim is not in repository !");
}

bool InMemoryRepository::repositoryUpdateVictim(const Victim& victim)
{
	if (std::find(this->victims.begin(), this->victims.end(), victim) != this->victims.end())
	{
		this->victims.erase(std::remove(this->victims.begin(), this->victims.end(), victim), this->victims.end());
		this->victims.push_back(victim);
		return true;
	}
	else
		throw RepositoryException("This victim is not in repository !");
}

std::vector<Victim> InMemoryRepository::repositoryGetAllVictims() const
{
	return this->victims;
}

Victim InMemoryRepository::repositoryGetVictim(const Victim& victim) const
{
	if (std::find(this->victims.begin(), this->victims.end(), victim) == this->victims.end())
		throw RepositoryException("This victim is not in repository !");
	for (Victim victimFromRepository : this->victims)
		if (victimFromRepository == victim)
			return victimFromRepository;
}

Victim InMemoryRepository::repositoryNext()
{
	if (this->indexIterator >= victims.size())
		this->indexIterator = 0;
	return this->victims[this->indexIterator++];
}

bool InMemoryRepository::repositoryExistVictim(const Victim& victim)
{
	for (Victim victimRepository : this->victims)
		if (victimRepository == victim)
			return true;
	return false;
}

