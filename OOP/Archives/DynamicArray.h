#pragma once
#include "Domain.h"
#define CAPACITY 10

typedef void* TypeElement;

typedef struct 
{
	int capacity;
	int size;
	TypeElement* elements;
} DynamicArray;

DynamicArray* createDynamicArray(int capacity);
/*
creates a DynamicArray
input : capacity - integer
output : a pointer to a DynamicArray
*/
DynamicArray* createCopyArray(DynamicArray* vector);
/*
creates a copy of a DynamicArray
input : a pointer to an existing DynamicArray
output : a pointer to a new DynamicArray
*/
int resizeArray(DynamicArray* vector);
/*
resie the Array
input : a pointer to a DynamicArray
output : 0 - resize succedded, -1 otherwise
*/
void addElementArray(DynamicArray* vector, TypeElement element);
/*
add an element to an array
input : vector - a pointer to a DynamicArray, element - a pointer to a structure
output : 
*/
int existArchiveArray(DynamicArray* vector, Archive* archive);
/*
checks if an Archive is in a DynamicArray
input : vector - a pointer to a DynamicArray, archive - a pointer to an archive
output : 1 - the archive is in vector, 0 - otherwise
*/
int getPositionArchive(DynamicArray* vector, Archive* archive);
/*
get the position of an archive in a specified array
input : vector - pointer to a DynamicArray, archive - pointer to an Archive
output : p - if the archive is in vector on position p, -1 - otherwise
*/
void deleteElementArray(DynamicArray* vector, int position);
/*
delete an element to an array
input : vector - a pointer to a DynamicArray, element - a pointer to a structure
output : 
*/
void updateElementArray(DynamicArray* vector, int position, TypeElement element);
/*
update an element to an array
input : vector - a pointer to a DynamicArray, element - a pointer to a structure
output :
*/
int getSizeArray(DynamicArray* vector);
TypeElement getElementOnPositionArray(DynamicArray* vector, int position);
/*
return a pointer to the element on position 'position' in vector
input : vector - pointer to a DynamicArray, position - integer
output : pointer to specified element, NULL otherwise
*/
void destroyDynamicArrayOfArchives(DynamicArray* vector);
void destroyDynamicArrayOfLists(DynamicArray* vector);
void destroyDynamicArrayOfOperations(DynamicArray* vector);
