#pragma once
#include "Repository.h"
#include "InFileRepository.h"

using namespace std;

class Operation
{
protected :
	shared_ptr<Repository> repository;
	Victim victimToUndo;
	Victim victimToRedo;
public :
	Operation(shared_ptr<Repository> repository, Victim victimUndo, Victim victimRedo);
	virtual void executeUndo()=0;
	virtual void executeRedo() = 0;
	virtual ~Operation() { };
};

class OperationAdd : public Operation
{
public :
	OperationAdd(shared_ptr<Repository> repository, Victim victimUndo, Victim victimRedo) : Operation(repository, victimUndo, victimRedo) {}
	void executeUndo() override;
	void executeRedo() override;
};

class OperationDelete : public Operation
{
public :
	OperationDelete(shared_ptr<Repository> repository, Victim victimUndo, Victim victimRedo) : Operation(repository, victimUndo, victimRedo) {}
	void executeUndo() override;
	void executeRedo() override;
};

class OperationUpdate : public Operation
{
public:
	OperationUpdate(shared_ptr<Repository> repository, Victim victimUndo, Victim victimRedo) : Operation(repository, victimUndo, victimRedo) {}
	void executeUndo() override;
	void executeRedo() override;
};