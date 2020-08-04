#pragma once
#include "Repository.h"
#include "StackLists.h"
#include "StackOperations.h"

typedef struct {
	Repository* repository;
	Stack* stackLists;
	StackOperations* stackOperations;
	int caseStack;
} Service;

Service* createService(Repository* repository);
int serviceAddArchive(Service* service, int archiveCatalogueNumber, char stateOfDeterioration[], char fileType[], int yearOfCreation);
/*
create and add, if possible, an archive
input : service - pointer to a Service structure, the others - parameters for an archive
output : 1 - archive was successfully added, 0 - otherwise
*/
int serviceUpdateArchive(Service* service, int archiveCatalogueNumber, char stateOfDeterioration[], char fileType[], int yearOfCreation);
/*
create and update, if possible, an archive
input : service - pointer to a Service structure, the others - parameters for an archive
output : 1 - archive was successfully updated, 0 - otherwise
*/
int serviceDeleteArchive(Service* service, int archiveCatalogueNumber);
/*
create and delete, if possible, an archive
input : service - pointer to a Service structure, archiveCatalogueNumber - the number for an archive, this works as an id
output : 1 - archive was successfully deleted, 0 - otherwise
*/
DynamicArray* serviceGetAllArchives(Service* service);
/*
return a pointer to a DynamicArray containing copies of all archives from repository
input : service - pointer to a Service structure
output : a pointer to a DynamicArray containing copies of all archives from repository
*/
DynamicArray* serviceGetFilteredByType(Service* service, char fileType[]);
/*
return a pointer to a DynamicArray containing all archives having a specified fileType
input : service - pointer to a Service structure, fileType - string
output : a pointer to a DynamicArray containing all archives having a specified fileType
*/
DynamicArray* serviceGetFilteredByYear(Service* service, int yearOfCreation);
/*
return a pointer to a DynamicArray having all archives whose year is smaller than yearOfCreation
input : service - pointer to a Service structure, yearOfCreation - integer
output : a pointer to a DynamicArray having all archives whose year is smaller than yearOfCreation
*/
int serviceRedo(Service* service);
/*
redo, if possible, the last operation
input : service - pointer to a Service structure
output : 1 - redo was successful, 0 -otherwise
*/
int serviceUndo(Service* service);
/*
undo, if possible, the last operation
input : service - pointer to a Service structure
output : 1 - undo was successful, 0 -otherwise
*/
void destroyService(Service* service);

