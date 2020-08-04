#pragma once
#include "Domain.h"
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "Exceptions.h"

class Repository
{
protected :
	int indexIterator;
public:
	Repository() : indexIterator(0) {}
	virtual bool repositoryAddVictim(const Victim& victim)=0;
	virtual bool repositoryDeleteVictim(const Victim& victim)=0;
	virtual bool repositoryUpdateVictim(const Victim& victim)=0;
	virtual std::vector<Victim> repositoryGetAllVictims() const =0;
	virtual Victim repositoryGetVictim(const Victim& victim) const =0;
	virtual bool repositoryExistVictim(const Victim& victim) = 0;
	virtual Victim repositoryNext()=0;
	virtual void setFileName(std::string nameOfFile)=0;
	virtual std::string getFileName()=0;
	virtual ~Repository() {}
};


class InMemoryRepository :  public Repository
{
private :
	std::vector<Victim> victims;
public :
	InMemoryRepository() {}
	bool repositoryAddVictim(const Victim& victim) override;
	bool repositoryDeleteVictim(const Victim& victim) override;
	bool repositoryUpdateVictim(const Victim& victim) override;
	std::vector<Victim> repositoryGetAllVictims() const override;
	Victim repositoryGetVictim(const Victim& victim) const override;
	Victim repositoryNext() override;
	bool repositoryExistVictim(const Victim& victim) override;
	void setFileName(std::string nameOfFile) {};
	std::string getFileName() { return ""; };
	~InMemoryRepository() {}
};
