#pragma once
#include "DynamicArray.h"
#include "Domain.h"

typedef struct
{
	DynamicArray* operations;
	int index;
	int lengthOfOperations;
} StackOperations;

StackOperations* createStackOperation();
void stackOperationdAddOperation(StackOperations* stackOperations, Operation* operation);
/*
add an Operation to stack of operations
input : stackOperation - pointer to a stack of operations, operation - pointer to an Operation structure
output : -
*/
int stackOperationsUndo(StackOperations* stackOperations);
/*
undo the last operation of possible
input : stack - pointer to a stack of operations
output : 1 - successful undo, 0 - otherwise
*/
int stackOperationsRedo(StackOperations* stackOperations);
/*
redo the last operation of possible
input : stack - pointer to a stack of operations
output : 1 - successful redo, 0 - otherwise
*/
Operation* getLastOperation(StackOperations* stackOperations);
/*
return the last performed operation excepting undo redo
input : stack - pointer to a stack of operations
output : a pointer to the last performed operation excepting undo redo
*/
void destroyStackOperation(StackOperations* stackOperations);