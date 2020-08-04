#include "StackLists.h"
#include <stdlib.h>
#include <string.h>

Stack* createStack()
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL)
		return NULL;
	stack->lists = createDynamicArray(10);
	stack->index = 0;
	stack->lengthOfLists = 0;
	return stack;
}

void stackAddList(Stack* stack, DynamicArray* list)
{
	if (stack == NULL || list == NULL)
		return NULL;
	addElementArray(stack->lists, list);
	stack->index = stack->index + 1;
	stack->lengthOfLists = stack->index;
}

int stackUndo(Stack* stack)
{
	if (stack == NULL)
		return 0;
	if (stack->index == 0)
		return  0;
	stack->index = stack->index - 1;
	return 1;
}

int stackRedo(Stack* stack)
{
	if (stack == NULL)
		return 0;
	if (stack->index != stack->lengthOfLists)
	{
		stack->index = stack->index + 1;
		return 1;
	}
	return 0;
}

DynamicArray* stackGetLastList(Stack* stack)
{
	if (stack == NULL)
		return NULL;
	if (stack->index == 0)
		return NULL;
	return getElementOnPositionArray(stack->lists, stack->index - 1);
}

void destroyStack(Stack* stack)
{
	if (stack == NULL)
		return NULL;
	destroyDynamicArrayOfLists(stack->lists);
	free(stack);
}