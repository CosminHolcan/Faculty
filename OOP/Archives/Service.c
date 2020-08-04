#include "Service.h"
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdio.h>

Service* createService(Repository* repository)
{
	Service* service = (Service*)malloc(sizeof(Service));
	if (service == NULL)
		return NULL;
	service->repository = repository;
	service->stackLists = createStack();
	service->stackOperations = createStackOperation();
	service->caseStack = 2;
	return service;
}

int serviceAddArchive(Service* service, int archiveCatalogueNumber, char stateOfDeterioration[], char fileType[], int yearOfCreation)
{
	Archive* archive = createArchive(archiveCatalogueNumber, stateOfDeterioration, fileType, yearOfCreation);
	int result;
	result = repositoryAddArchive(service->repository, archive);
	if (result == 1)
	{
		if (service->caseStack == 1)
			stackAddList(service->stackLists, repositoryGetAllArchives(service->repository));
		else
		{
			Archive* copy_archive = createCopyArchive(archive);
			Archive* another_copy_archive = createCopyArchive(archive);
			Operation* operation = createOperation(copy_archive, another_copy_archive, "add");
			stackOperationdAddOperation(service->stackOperations, operation);
		}

	}
	else
		destroyArchive(archive);
	return result;
}

int serviceUpdateArchive(Service* service, int archiveCatalogueNumber, char stateOfDeterioration[], char fileType[], int yearOfCreation)
{
	Archive* archive = createArchive(archiveCatalogueNumber, stateOfDeterioration, fileType, yearOfCreation);
	int result;
	Archive* archive_from_repository = createCopyArchive(repositoryGetArchive(service->repository, archive));
	result = repositoryUpdateArchive(service->repository, archive);
	if (result == 1)
	{
		if (service->caseStack == 1)
		{
			stackAddList(service->stackLists, repositoryGetAllArchives(service->repository));
			destroyArchive(archive_from_repository);
		}
		else
		{
			Archive* archiveRedo = createCopyArchive(archive);
			Archive* archiveUndo = archive_from_repository;
			Operation* operation = createOperation(archiveRedo, archiveUndo, "update");
			stackOperationdAddOperation(service->stackOperations, operation);
		}

	}
	else
		destroyArchive(archive);
	return result;
}

int serviceDeleteArchive(Service* service, int archiveCatalogueNumber)
{
	Archive* archive = createArchive(archiveCatalogueNumber, " ", " ", 0);
	int result;
	Archive* archive_from_repository = createCopyArchive(repositoryGetArchive(service->repository, archive));
	result = repositoryDeleteArchive(service->repository, archive);
	if (result == 1)
	{
		if (service->caseStack == 1)
		{
			stackAddList(service->stackLists, repositoryGetAllArchives(service->repository));
			destroyArchive(archive_from_repository);
			destroyArchive(archive);
		}
		else
		{
			Archive* archiveRedo = archive;
			Archive* archiveUndo = archive_from_repository;
			Operation* operation = createOperation(archiveRedo, archiveUndo, "delete");
			stackOperationdAddOperation(service->stackOperations, operation);
		}
	}
	else
		destroyArchive(archive);
	return result;
}


DynamicArray* serviceGetAllArchives(Service* service)
{
	return repositoryGetAllArchives(service->repository);
}

DynamicArray* serviceGetFilteredByType(Service* service, char fileType[])
{
	DynamicArray* vector_from_repository = repositoryGetAllArchives(service->repository);
	DynamicArray* vector_to_ui = createDynamicArray(10);
	Archive* archive, *copy_archive;
	for (int index = 0; index < vector_from_repository->size; index++)
	{
		archive = getElementOnPositionArray(vector_from_repository, index);
		if (strcmp(getFileType(archive), fileType) == 0)
		{
			copy_archive = createCopyArchive(archive);
			addElementArray(vector_to_ui, copy_archive);
		}
	}
	destroyDynamicArrayOfArchives(vector_from_repository);
	return vector_to_ui;
}

DynamicArray* serviceGetFilteredByYear(Service* service, int yearOfCreation)
{
	DynamicArray* vector_from_repository = repositoryGetAllArchives(service->repository);
	DynamicArray* vector_to_ui = createDynamicArray(10);
	Archive* archive, *archive1, *archive2, *auxiliary_archive, *copy_archive;
	for (int index = 0; index < vector_from_repository->size; index++)
	{
		archive = getElementOnPositionArray(vector_from_repository, index);
		if (getYearOfCreation(archive) < yearOfCreation)
		{
			copy_archive = createCopyArchive(archive);
			addElementArray(vector_to_ui, copy_archive);
		}
	}
	
	for (int index1 = 0; index1 < vector_to_ui->size-1; index1++)
	{
		archive1 = getElementOnPositionArray(vector_to_ui, index1);
		for (int index2 = index1 + 1; index2 < vector_to_ui->size; index2++)
		{
			archive2 = getElementOnPositionArray(vector_to_ui, index2);
			if (strcmp(getStateOfDeterioration(archive1), getStateOfDeterioration(archive2)) > 0)
			{
				auxiliary_archive = vector_to_ui->elements[index1];
				vector_to_ui->elements[index1] = vector_to_ui->elements[index2];
				vector_to_ui->elements[index2] = auxiliary_archive;
			}
		}
	}
	destroyDynamicArrayOfArchives(vector_from_repository);
	return vector_to_ui;
	
}

int serviceUndo(Service* service)
{
	if (service->caseStack == 1)
	{
		if (service == NULL)
			return 0;
		int result = stackUndo(service->stackLists);
		if (result == 1)
		{
			Repository* repository = service->repository;
			destroyDynamicArrayOfArchives(repository->archives);
			DynamicArray* copyList = createCopyArray(stackGetLastList(service->stackLists));
			repository->archives = copyList;
		}
		return result;
	}
	else 
	{ 
	if (service == NULL)
		return 0;
	int result = stackOperationsUndo(service->stackOperations);
	if (result == 1)
	{
		Operation* operation = getLastOperation(service->stackOperations);
		Archive* archiveUndo = operationGetArchiveUndo(operation);
		if (strcmp(operationGetStringOperation(operation), "add") == 0)
			repositoryDeleteArchive(service->repository, archiveUndo);
		if (strcmp(operationGetStringOperation(operation), "update") == 0)
		{
			repositoryUpdateArchive(service->repository, createCopyArchive(archiveUndo));
		}
		if (strcmp(operationGetStringOperation(operation), "delete") == 0)
		{
			repositoryAddArchive(service->repository, createCopyArchive(archiveUndo));
		}
		service->stackOperations->index = service->stackOperations->index - 1;
	}
	return result;
	}
}

int serviceRedo(Service* service)
{
	if (service->caseStack == 1)
	{
		if (service == NULL)
			return 0;
		int result = stackRedo(service->stackLists);
		if (result == 1)
		{
			Repository* repository = service->repository;
			destroyDynamicArrayOfArchives(repository->archives);
			DynamicArray* copyList = createCopyArray(stackGetLastList(service->stackLists));
			repository->archives = copyList;
		}
		return result;
	}
	else 
	{
		if (service == NULL)
			return 0;
		int result = stackOperationsRedo(service->stackOperations);
		if (result == 1)
		{
			Operation* operation = getLastOperation(service->stackOperations);
			Archive* archiveRedo = operationGetArchiveRedo(operation);
			if (strcmp(operationGetStringOperation(operation), "add") == 0)
			{
				repositoryAddArchive(service->repository, createCopyArchive(archiveRedo));
			}
			if (strcmp(operationGetStringOperation(operation), "update") == 0)
			{
				repositoryUpdateArchive(service->repository, createCopyArchive(archiveRedo));
			}
			if (strcmp(operationGetStringOperation(operation), "delete") == 0)
				repositoryDeleteArchive(service->repository, archiveRedo);

		}
		return result;
	}
}

void destroyService(Service* service)
{
	destroyRepository(service->repository);
	destroyStack(service->stackLists);
	destroyStackOperation(service->stackOperations);
	free(service);
}