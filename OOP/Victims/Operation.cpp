#include "Operation.h"

Operation::Operation(shared_ptr<Repository> repository, Victim victimUndo, Victim victimRedo) :
	repository(repository), victimToUndo(victimUndo), victimToRedo(victimRedo)
{
}

// OperationAdd

void OperationAdd::executeUndo()
{
	this->repository->repositoryDeleteVictim(this->victimToUndo);
}

void OperationAdd::executeRedo()
{
	this->repository->repositoryAddVictim(this->victimToRedo);
}


// OperationDelete

void OperationDelete::executeUndo()
{
	this->repository->repositoryAddVictim(this->victimToUndo);
}

void OperationDelete::executeRedo()
{
	this->repository->repositoryDeleteVictim(this->victimToRedo);
}


// OperationUpdate

void OperationUpdate::executeUndo()
{
	this->repository->repositoryUpdateVictim(this->victimToUndo);
}

void OperationUpdate::executeRedo()
{
	this->repository->repositoryUpdateVictim(this->victimToRedo);
}
