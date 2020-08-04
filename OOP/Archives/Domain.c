#include "Domain.h"
#include <stdlib.h>
#include <string.h>

Archive* createArchive(int archiveCatalogueNumber, char stateOfDeterioration[], char fileType[], int yearOfCreation)
{
	Archive* archive = (Archive*)malloc(sizeof(Archive));
	if (archive == NULL)
		return NULL;
	archive->archiveCatalogueNumber = archiveCatalogueNumber;
	strcpy(archive->stateOfDeterioration, stateOfDeterioration);
	strcpy(archive->fileType, fileType);
	archive->yearOfCreation = yearOfCreation;
	return archive;
}

Archive* createCopyArchive(Archive* archive)
{
	if (archive == NULL)
		return NULL;
	Archive* new_archive = createArchive(getArchiveCatalogueNumber(archive), getStateOfDeterioration(archive),
		getFileType(archive), getYearOfCreation(archive));
	return new_archive;

}

int getArchiveCatalogueNumber(Archive* archive)
{
	if (archive == NULL)
		return -1;
	return archive->archiveCatalogueNumber;
}

char* getStateOfDeterioration(Archive* archive)
{
	if (archive == NULL)
		return NULL;
	return archive->stateOfDeterioration;
}

char* getFileType(Archive* archive)
{
	if (archive == NULL)
		return NULL;
	return archive->fileType;
}

int getYearOfCreation(Archive* archive)
{
	if (archive == NULL)
		return -1;
	return archive->yearOfCreation;
}

void destroyArchive(Archive* archive)
{
	if (archive == NULL)
		return;
	free(archive);
}

Operation* createOperation(Archive* archive_redo, Archive* archive_undo, char string_operation[])
{
	Operation* operation = (Operation*)malloc(sizeof(Operation));
	if (operation == NULL)
		return NULL;
	operation->archive_redo = archive_redo;
	operation->archive_undo = archive_undo;
	strcpy(operation->string_operation, string_operation);
	return operation;
}

Archive* operationGetArchiveRedo(Operation* operation)
{
	if (operation == NULL)
		return NULL;
	return operation->archive_redo;
}

Archive* operationGetArchiveUndo(Operation* operation)
{
	if (operation == NULL)
		return NULL;
	return operation->archive_undo;
}

char* operationGetStringOperation(Operation* operation)
{
	if (operation == NULL)
		return NULL;
	return operation->string_operation;
}

void destroyOperation(Operation* operation)
{
	destroyArchive(operation->archive_redo);
	destroyArchive(operation->archive_undo);
	free(operation);
}