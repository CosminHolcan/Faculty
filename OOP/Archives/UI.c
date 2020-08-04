#include "UI.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

UI* createUI(Service* service)
{
	UI* ui_variable = (UI*)malloc(sizeof(UI));
	if (ui_variable == NULL)
		return NULL;
	ui_variable->service = service;
	return ui_variable;
}

void uiAddArchive(UI* ui_variable, char* pointer_to_separate)
{
	int archiveNumber, yearCreation, result;
	char archiveCatalogueNumber[50], stateOfDeterioration[50], fileType[50], yearOfCreation[50], separators[] = " ,\n";
	pointer_to_separate = strtok(NULL, separators);
	strcpy(archiveCatalogueNumber, pointer_to_separate);
	pointer_to_separate = strtok(NULL, separators);
	strcpy(stateOfDeterioration, pointer_to_separate);
	pointer_to_separate = strtok(NULL, separators);
	strcpy(fileType, pointer_to_separate);
	pointer_to_separate = strtok(NULL, separators);
	strcpy(yearOfCreation, pointer_to_separate);
	sscanf(archiveCatalogueNumber, "%d", &archiveNumber);
	sscanf(yearOfCreation, "%d", &yearCreation);
	result = serviceAddArchive(ui_variable->service, archiveNumber, stateOfDeterioration, fileType, yearCreation);
	if (result == 0)
		printf("No!\n");
}

void uiUpdateArchive(UI* ui_variable, char* pointer_to_separate)
{
	int archiveNumber, yearCreation, result;
	char archiveCatalogueNumber[50], stateOfDeterioration[50], fileType[50], yearOfCreation[50], separators[] = " ,\n";
	pointer_to_separate = strtok(NULL, separators);
	strcpy(archiveCatalogueNumber, pointer_to_separate);
	pointer_to_separate = strtok(NULL, separators);
	strcpy(stateOfDeterioration, pointer_to_separate);
	pointer_to_separate = strtok(NULL, separators);
	strcpy(fileType, pointer_to_separate);
	pointer_to_separate = strtok(NULL, separators);
	strcpy(yearOfCreation, pointer_to_separate);
	sscanf(archiveCatalogueNumber, "%d", &archiveNumber);
	sscanf(yearOfCreation, "%d", &yearCreation);
	result = serviceUpdateArchive(ui_variable->service, archiveNumber, stateOfDeterioration, fileType, yearCreation);
	if (result == 0)
		printf("No!\n");
}

void uiDeleteArchive(UI* ui_variable, char* pointer_to_separate)
{
	int archiveNumber, result;
	char archiveCatalogueNumber[50], separators[] = " ,\n";
	pointer_to_separate = strtok(NULL, separators);
	strcpy(archiveCatalogueNumber, pointer_to_separate);
	sscanf(archiveCatalogueNumber, "%d", &archiveNumber);
	result = serviceDeleteArchive(ui_variable->service, archiveNumber);
	if (result == 0)
		printf("No!\n");
}

void uiPrintAll(UI* ui_variable)
{
	DynamicArray* vector_to_print = serviceGetAllArchives(ui_variable->service);
	if (vector_to_print == NULL)
		return NULL;
	for (int index = 0; index < vector_to_print->size; index++)
	{
		Archive* archive = getElementOnPositionArray(vector_to_print, index);
		if (archive != NULL)
			printf("Number : %d, State : %s, Type : %s, Year : %d.\n", getArchiveCatalogueNumber(archive),
				getStateOfDeterioration(archive), getFileType(archive), getYearOfCreation(archive));
	}
	destroyDynamicArrayOfArchives(vector_to_print);
}

void uiPrintFilteredByType(UI* ui_variable, char fileType[])
{
	DynamicArray* vector_to_print = serviceGetFilteredByType(ui_variable->service, fileType);
	for (int index = 0; index < vector_to_print->size; index++)
	{
		Archive* archive = getElementOnPositionArray(vector_to_print, index);
		if (archive != NULL)
			printf("Number : %d, State : %s, Type : %s, Year : %d.\n", getArchiveCatalogueNumber(archive),
				getStateOfDeterioration(archive), getFileType(archive), getYearOfCreation(archive));
	}
	destroyDynamicArrayOfArchives(vector_to_print);
}

void uiPrintFilteredByYear(UI* ui_variable, char* pointer_to_separate)
{
	int yearOfCreation;
	sscanf(pointer_to_separate, "%d", &yearOfCreation);
	DynamicArray* vector_to_print = serviceGetFilteredByYear(ui_variable->service, yearOfCreation);
	for (int index = 0; index < vector_to_print->size; index++)
	{
		Archive* archive = getElementOnPositionArray(vector_to_print, index);
		if (archive != NULL)
			printf("Number : %d, State : %s, Type : %s, Year : %d.\n", getArchiveCatalogueNumber(archive),
				getStateOfDeterioration(archive), getFileType(archive), getYearOfCreation(archive));
	}
	destroyDynamicArrayOfArchives(vector_to_print);
}

void uiUndo(UI* ui_variable)
{
	int result = serviceUndo(ui_variable->service);
}

void uiRedo(UI* ui_variable)
{
	int result = serviceRedo(ui_variable->service);
}

void menu(UI* ui_variable)
{
	char input[250], separators[] = " ,\n", * pointer_to_separate;
	while (1)
	{
		fgets(input, 250, stdin);
		pointer_to_separate = strtok(input, separators);
		if (strcmp(pointer_to_separate, "add") == 0)
			uiAddArchive(ui_variable, pointer_to_separate);
		else if (strcmp(pointer_to_separate, "update") == 0)
			uiUpdateArchive(ui_variable, pointer_to_separate);
		else if (strcmp(pointer_to_separate, "delete") == 0)
			uiDeleteArchive(ui_variable, pointer_to_separate);
		else if (strcmp(pointer_to_separate, "list") == 0)
		{
			pointer_to_separate = strtok(NULL, separators);
			if (pointer_to_separate == NULL)
				uiPrintAll(ui_variable);
			else
			{
				if (pointer_to_separate[0] >= '0' && pointer_to_separate[0] <= '9')
					uiPrintFilteredByYear(ui_variable, pointer_to_separate);
				else
					uiPrintFilteredByType(ui_variable, pointer_to_separate);
			}
		}

		else if (strcmp(pointer_to_separate, "undo") == 0)
			uiUndo(ui_variable);
		else if (strcmp(pointer_to_separate, "redo") == 0)
			uiRedo(ui_variable);

		else if (strcmp(pointer_to_separate, "exit") == NULL)
			return;
		else
			printf("This is not a valid command !\n");
	}
}

void destroyUI(UI* ui_variable)
{
	destroyService(ui_variable->service);
	free(ui_variable);
}
