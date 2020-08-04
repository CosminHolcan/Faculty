#pragma once

typedef struct
{
	int archiveCatalogueNumber;
	char stateOfDeterioration[20];
	char fileType[20];
	int yearOfCreation;
} Archive;

typedef struct
{
	Archive* archive_redo;
	Archive* archive_undo;
	char string_operation[10];
} Operation;

Archive* createArchive(int archiveCatalogueNumber, char stateOfDeterioration[], char fileType[], int yearOfCreation);
/*
creates a structure of type Archive
input : archiveCatalogueNumber - integer, stateOfDeterioration - string, fileType - string, yearOfCreation - integer
output : a pointer to an Archive
*/
Archive* createCopyArchive(Archive* archive);
/*
creates an Archive copy, having the same attributes as the input
input : archive - an Archive structure
output : a pointer to a new archive
*/
int getArchiveCatalogueNumber(Archive* archive);
char* getStateOfDeterioration(Archive* archive);
char* getFileType(Archive* archive);
int getYearOfCreation(Archive* archive);
void destroyArchive(Archive* archive);
/*
eliminate the archive and free the allocated space from memory
input : archive - an Archive structure
*/
Operation* createOperation(Archive* archive_redo, Archive* archive_undo, char string_operation[]);
/*
creates an Operation structure
input : archiveRedo, archiveUndo - Archive structures, string_operation - string
output : an Operation structure
*/
Archive* operationGetArchiveRedo(Operation* operation);
Archive* operationGetArchiveUndo(Operation* operation);
char* operationGetStringOperation(Operation* operation);
void destroyOperation(Operation* operation);
/*
eliminate the operation and free the allocated space from memory
input : an Operation structure
*/