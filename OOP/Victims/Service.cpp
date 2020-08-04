#include "Service.h"



std::vector<Victim> Service::serviceGetVictims() const {
	return this->repository->repositoryGetAllVictims();
}

bool Service::serviceAddVictim(const std::string& name, const std::string& placeOfOrigin, int age, const std::string& photograph)
{
	Victim victim{ name, placeOfOrigin, age, photograph };
	bool result = this->repository->repositoryAddVictim(victim);
	if (result)
	{
		this->operationsRedoRepository.clear();
		Victim victimUndo(name, placeOfOrigin, age, photograph);
		Victim victimRedo(name, placeOfOrigin, age, photograph);
		shared_ptr<Operation> operation = make_shared<OperationAdd>(this->repository, victimUndo, victimRedo);
		this->operationsUndoRepository.push_back(operation);
	}
	return result;
}

bool Service::serviceDeleteVictim(const std::string& name)
{
	Victim victim{ name, "", 0, "" };
	Victim victimRedo(name, "", 0, ""), victimUndo;
	if (this->repository->repositoryExistVictim(victim))
		victimUndo = this->repository->repositoryGetVictim(victim);
	bool result = this->repository->repositoryDeleteVictim(victim);
	if (result)
	{
		if (this->mylist->repositoryExistVictim(victim))
		{
			this->mylist->repositoryDeleteVictim(victim);
			this->notify();
		}
		this->operationsRedoRepository.clear();
		shared_ptr<Operation> operation = make_shared<OperationDelete>(this->repository, victimUndo, victimRedo);
		this->operationsUndoRepository.push_back(operation);
	}
	return result;
}

bool Service::serviceUpdateVictim(const std::string& name, const std::string& placeOfOrigin, int age, const std::string& photograph)
{
	Victim victim{ name, placeOfOrigin, age, photograph };
	Victim victimRedo(name, placeOfOrigin, age, photograph), victimUndo;
	if (this->repository->repositoryExistVictim(victim))
		victimUndo = this->repository->repositoryGetVictim(victim);
	bool result = this->repository->repositoryUpdateVictim(victim);
	if (result)
	{
		if (this->mylist->repositoryExistVictim(victim))
		{
			this->mylist->repositoryUpdateVictim(victim);
			this->notify();
		}
		this->operationsRedoRepository.clear();
		shared_ptr<Operation> operation = make_shared<OperationUpdate>(this->repository, victimUndo, victimRedo);
		this->operationsUndoRepository.push_back(operation);
	}
	return result;
}

void Service::serviceUndoRepository()
{
	if (this->operationsUndoRepository.size() == 0)
		throw exception("Undo operation can't be done!\n");
	shared_ptr<Operation> operation = this->operationsUndoRepository[this->operationsUndoRepository.size() - 1];
	this->operationsUndoRepository.pop_back();
	operation->executeUndo();
	this->operationsRedoRepository.push_back(operation);
}

void Service::serviceRedoRepository()
{
	if (this->operationsRedoRepository.size() == 0)
		throw exception("Redo operation can't be done!\n");
	shared_ptr<Operation> operation = this->operationsRedoRepository[this->operationsRedoRepository.size() - 1];
	this->operationsRedoRepository.pop_back();
	operation->executeRedo();
	this->operationsUndoRepository.push_back(operation);
}


Victim Service::serviceNext() const
{
	return this->repository->repositoryNext();
}


bool Service::serviceSaveVictim(const std::string& name)
{
	Victim victim_from_ui{ name, "", 0, "" };
	this->repository->repositoryGetVictim(victim_from_ui);
	Victim victim_from_repository = this->repository->repositoryGetVictim(victim_from_ui);
	Victim victimUndo = this->repository->repositoryGetVictim(victim_from_ui);
	Victim victimRedo = this->repository->repositoryGetVictim(victim_from_ui);
	this->mylist->repositoryAddVictim(victim_from_repository);
	this->notify();
	this->operationsRedoMylist.clear();
	shared_ptr<Operation> operation = make_shared<OperationAdd>(this->mylist, victimUndo, victimRedo);
	this->operationsUndoMylist.push_back(operation);
	return true;
}

void Service::serviceUndoMylist()
{
	if (this->operationsUndoMylist.size() == 0)
		throw exception("Undo operation can't be done!\n");
	shared_ptr<Operation> operation = this->operationsUndoMylist[this->operationsUndoMylist.size() - 1];
	this->operationsUndoMylist.pop_back();
	operation->executeUndo();
	this->notify();
	this->operationsRedoMylist.push_back(operation);
}

void Service::serviceRedoMylist()
{
	if (this->operationsRedoMylist.size() == 0)
		throw exception("Redo operation can't be done!\n");
	shared_ptr<Operation> operation = this->operationsRedoMylist[this->operationsRedoMylist.size() - 1];
	this->operationsRedoMylist.pop_back();
	operation->executeRedo();
	this->notify();
	this->operationsUndoMylist.push_back(operation);
}

std::vector<Victim> Service::serviceGetFilteredWithPlace(const std::string& placeOfOrigin, int age)
{
	std::vector<Victim> victims_from_repository = this->repository->repositoryGetAllVictims();
	std::vector<Victim> victims_to_ui;
	std::copy_if(victims_from_repository.begin(), victims_from_repository.end(), std::back_inserter(victims_to_ui),
		[placeOfOrigin, age](Victim victim) { return victim.getPlaceOfOrigin() == placeOfOrigin && victim.getAge() < age; });
	return victims_to_ui;
}

std::vector<Victim> Service::serviceGetFilteredWithoutPlace(int age)
{
	std::vector<Victim> victims_from_repository = this->repository->repositoryGetAllVictims();
	std::vector<Victim> victims_to_ui;
	std::copy_if(victims_from_repository.begin(), victims_from_repository.end(), std::back_inserter(victims_to_ui),
		[age](Victim victim) { return victim.getAge() < age; });
	return victims_to_ui;
}

void Service::serviceSetFileInRepository(std::string nameOfFile)
{
	this->repository = make_shared<InFileRepository>();
	this->repository->setFileName(nameOfFile);
}

void Service::serviceSetFileMyList(std::string nameOfFile)
{
	ifstream inputFile{ nameOfFile };
	this->mylist = make_shared<InFileRepository>();
	this->mylist->setFileName(nameOfFile);
}

std::vector<Victim> Service::serviceGetVictimsMylist()
{
	return this->mylist->repositoryGetAllVictims();
}

std::string Service::serviceGetFileMyList()
{
	return this->mylist->getFileName();
}

Service::~Service()
{

}
