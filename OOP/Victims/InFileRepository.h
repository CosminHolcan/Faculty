#pragma once
#include "Repository.h"

class InFileRepository : public Repository
{
private:
	std::string fileName;
public:
	InFileRepository() {}
	bool repositoryAddVictim(const Victim& victim) override;
	bool repositoryDeleteVictim(const Victim& victim) override;
	bool repositoryUpdateVictim(const Victim& victim) override;
	std::vector<Victim> repositoryGetAllVictims() const override;
	Victim repositoryGetVictim(const Victim& victim) const override;
	bool repositoryExistVictim(const Victim& victim) override;
	Victim repositoryNext() override;
	void setFileName(std::string nameOfFile);
	std::string getFileName();
	~InFileRepository() {}
};
