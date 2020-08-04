#pragma once
#include "Domain.h"
#include "DynamicArray.h"

typedef struct
{
	DynamicArray* archives;
} Repository;

Repository* createRepository();
int repositoryAddArchive(Repository* repository, Archive* archive);
/*
add, if possible, an Archive to repository
input : repository - pointer to a Repository, archive - pointer to an Archive
output : 1 - the archive was successfully added, 0 - otherwise
*/
int repositoryUpdateArchive(Repository* repository, Archive* archive);
/*
update, if possible, an Archive to repository
input : repository - pointer to a Repository, archive - pointer to an Archive
output : 1 - the archive was successfully updated, 0 - otherwise
*/
int repositoryDeleteArchive(Repository* repository, Archive* archive);
/*
remove, if possible, an Archive to repository
input : repository - pointer to a Repository, archive - pointer to an Archive
output : 1 - the archive was successfully removed, 0 - otherwise
*/
int getRepositorySize(Repository* repository);
Archive* getArchiveOnPosition(Repository* repository, int position);
Archive* repositoryGetArchive(Repository* repository, Archive* archive);
/*
return pointer to an archive from repository or NULL otherwise
input : repository - pointer to a Repository, archive - pointer to an Archive
output : pointer to an archive from repository or NULL otherwise
*/
DynamicArray* repositoryGetAllArchives(Repository* repository);
/*
return a copy of the array from repository
input : repository - pointer to a Repository
output : a pointer to a new Dynamic Array containing pointers to copies of all archives
*/
void destroyRepository(Repository* repository);
