#include "StackOperations.h"
#include <stdlib.h>
#include <string.h>

StackOperations* createStackOperation()
{
	StackOperations* stackOperation = (StackOperations*)malloc(sizeof(StackOperations));
	if (stackOperation == NULL)
		return NULL;
	stackOperation->operations = createDynamicArray(10);
	stackOperation->index = 0;
	stackOperation->lengthOfOperations = 0;
	return stackOperation;
}

void stackOperationdAddOperation(StackOperations* stackOperations, Operation* operation)
{
	if (stackOperations == NULL || stackOperations->operations == NULL)
		return NULL;
	addElementArray(stackOperations->operations, operation);
	stackOperations->index += 1;
	stackOperations->lengthOfOperations = stackOperations->index;
}

int stackOperationsUndo(StackOperations* stackOperations)
{
	if (stackOperations == NULL)
		return 0;
	if (stackOperations->index == 0)
		return  0;
	return 1;
}

int stackOperationsRedo(StackOperations* stackOperations)
{
	if (stackOperations == NULL)
		return 0;	
	if (stackOperations->index != stackOperations->lengthOfOperations)
	{
		stackOperations->index += 1;
		return 1;
	}
	return 0;
}

Operation* getLastOperation(StackOperations* stackOperations)
{
	if (stackOperations == NULL)
		return NULL;
	if (stackOperations->index == 0)
		return NULL;
	return getElementOnPositionArray(stackOperations->operations, stackOperations->index - 1);
}

void destroyStackOperation(StackOperations* stackOperations)
{
	if (stackOperations == NULL)
		return NULL;
	destroyDynamicArrayOfOperations(stackOperations->operations);
	free(stackOperations);
	stackOperations = NULL;
}