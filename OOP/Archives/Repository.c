#include "Repository.h"
#include <stdlib.h>
#include <string.h>

Repository* createRepository()
{
	Repository* repository = (Repository*)malloc(sizeof(Repository));
	if (repository == NULL)
		return NULL;
	repository->archives = createDynamicArray(CAPACITY);
	return repository;
}

int repositoryAddArchive(Repository* repository, Archive* archive)
{
	if (repository == NULL || archive == NULL)
		return 0;
	if (existArchiveArray(repository->archives, archive) == 0)
	{
		addElementArray(repository->archives, archive);
		return 1;
	}
	return 0;
}

int repositoryUpdateArchive(Repository* repository, Archive* archive)
{
	if (repository == NULL || archive == NULL)
		return 0;
	if (existArchiveArray(repository->archives, archive) == 1)
	{
		int position = getPositionArchive(repository->archives, archive);
		updateElementArray(repository->archives, position, archive);
		return 1;
	}
	return 0;
}

int repositoryDeleteArchive(Repository* repository, Archive* archive)
{
	if (repository == NULL || archive == NULL)
		return 0;
	if (existArchiveArray(repository->archives, archive) == 1)
	{
		int position = getPositionArchive(repository->archives, archive);
		deleteElementArray(repository->archives, position);
		return 1;
	}
	return 0;
}

int getRepositorySize(Repository* repository)
{
	if (repository == NULL)
		return -1;
	return getSizeArray(repository->archives);
}

Archive* getArchiveOnPosition(Repository* repository, int position)
{
	if (repository == NULL)
		return NULL;
	return getElementOnPositionArray(repository->archives, position);
}

Archive* repositoryGetArchive(Repository* repository, Archive* archive)
{
	if (repository == NULL || archive == NULL)
		return NULL;
	if (existArchiveArray(repository->archives, archive) == 1)
	{
		int position = getPositionArchive(repository->archives, archive);
		return getArchiveOnPosition(repository, position);
	}
	else return NULL;
}

DynamicArray* repositoryGetAllArchives(Repository* repository)
{
	if (repository == NULL)
		return NULL;
	DynamicArray* archives = createDynamicArray(10);
	int size = getSizeArray(repository->archives);
	for (int index = 0; index < size; index++)
	{
		Archive* archive = getElementOnPositionArray(repository->archives, index);
		Archive* copy_archive = createCopyArchive(archive);
		addElementArray(archives, copy_archive);
	}
	return archives;
}

void destroyRepository(Repository* repository)
{
	if (repository == NULL)
		return;
	destroyDynamicArrayOfArchives(repository->archives);
	free(repository);
}