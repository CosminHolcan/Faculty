#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>

DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* data = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (data == NULL)
		return NULL;
	data->capacity = capacity;
	data->size = 0;
	data->elements = (TypeElement*)malloc(capacity * sizeof(TypeElement));
	if (data->elements == NULL)
		return NULL;
	return data;
}

DynamicArray* createCopyArray(DynamicArray* vector)
{
	if (vector == NULL)
		return NULL;
	DynamicArray* copyArray = createDynamicArray(CAPACITY);
	int size = getSizeArray(vector);
	for (int index = 0; index < size; index++)
	{
		Archive* copyArchive = createCopyArchive(getElementOnPositionArray(vector, index));
		addElementArray(copyArray, copyArchive);
	}
	return copyArray;
}

int resizeArray(DynamicArray* vector)
{
	if (vector == NULL)
		return -1;
	vector->capacity = vector->capacity * 2;
	TypeElement* auxiliary_elements = (TypeElement*)malloc(vector->capacity * sizeof(TypeElement));
	if (auxiliary_elements == NULL)
		return -1;
	for (int index = 0; index < vector->size; index++)
		auxiliary_elements[index] = vector->elements[index];
	free(vector->elements);
	vector->elements = auxiliary_elements;
	return 0;
}

void addElementArray(DynamicArray* vector, TypeElement element)
{
	if (vector == NULL)
		return;
	if (vector->elements == NULL)
		return;
	if (vector->capacity == vector->size)
		resizeArray(vector);
	vector->elements[vector->size++] = element;
}

int existArchiveArray(DynamicArray* vector, Archive* archive)
{
	if (vector == NULL)
		return 0;
	if (vector->elements == NULL)
		return 0;
	for (int index = 0; index < vector->size; index++)
		if (getArchiveCatalogueNumber(vector->elements[index]) == getArchiveCatalogueNumber(archive))
			return 1;
	return 0;
}

int getPositionArchive(DynamicArray* vector, Archive* archive)
{
	if (existArchiveArray(vector, archive) == 1)
	{
		for (int index = 0; index <vector->size; index++)
			if (getArchiveCatalogueNumber(vector->elements[index]) == getArchiveCatalogueNumber(archive))
				return index;
	}
	else return -1;
}

void deleteElementArray(DynamicArray* vector, int position)
{
	Archive* archive_to_delete = vector->elements[position];
	for (int index = position; index < vector->size; index++)
		vector->elements[index] = vector->elements[index + 1];
	vector->elements[vector->size] = NULL;
	vector->size--;
	destroyArchive(archive_to_delete);
}

void updateElementArray(DynamicArray* vector, int position, TypeElement element)
{
	Archive* archive_to_update = vector->elements[position];
	vector->elements[position] = element;
	destroyArchive(archive_to_update);
}

int getSizeArray(DynamicArray* vector)
{
	if (vector == NULL)
		return -1;
	if (vector->elements == NULL)
		return -1;
	return vector->size;
}

TypeElement getElementOnPositionArray(DynamicArray* vector, int position)
{
	if (vector == NULL)
		return NULL;
	if (position < 0 || position >= vector->size)
		return NULL;
	return vector->elements[position];
}

void destroyDynamicArrayOfArchives(DynamicArray* vector)
{
	if (vector == NULL )
		return;
	for (int index = 0; index < vector->size; index++)
		destroyArchive(vector->elements[index]);
	free(vector->elements);
	vector->elements = NULL;
	free(vector);
	vector = NULL;

}

void destroyDynamicArrayOfLists(DynamicArray* vector)
{
	if (vector == NULL)
		return;
	for (int index = 0; index < vector->size; index++)
		destroyDynamicArrayOfArchives(vector->elements[index]);
	free(vector->elements);
	vector->elements = NULL;
	free(vector);
	vector = NULL;
}

void destroyDynamicArrayOfOperations(DynamicArray* vector)
{
	if (vector == NULL)
		return;
	for (int index = 0; index < vector->size; index++)
		destroyOperation(vector->elements[index]);
	free(vector->elements);
	vector->elements = NULL;
	free(vector);
	vector = NULL;
}