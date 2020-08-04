#pragma once
#include "DynamicArray.h"
#include "Domain.h"

typedef struct
{
	DynamicArray* lists;
	int index;
	int lengthOfLists;
} Stack;

Stack* createStack();
void stackAddList(Stack* stack, DynamicArray* list);
/*
add a vector of archives to stack
input : stack - pointer to a stack of lists, list - pointer to a DynamicArray with archives
output : -
*/
int stackUndo(Stack* stack);
/*
undo the last operation of possible
input : stack - pointer to a stack of lists
output : 1 - successful undo, 0 - otherwise
*/
int stackRedo(Stack* stack);
/*
redo the last operation of possible
input : stack - pointer to a stack of lists
output : 1 - successful redo, 0 - otherwise
*/
DynamicArray* stackGetLastList(Stack* stack);
/*
return the list of current archives
input : stack - pointer to a stack of lists
output : pointer to the DynamicArray of current archives
*/
void destroyStack(Stack* stack);
