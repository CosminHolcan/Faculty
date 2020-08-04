#pragma once
#include "Service.h"

typedef struct {
	Service* service;
} UI;

UI* createUI(Service* service);
void uiAddArchive(UI* ui_variable, char* pointer_to_separate);
void uiUpdateArchive(UI* ui_variable, char* pointer_to_separate);
void uiDeleteArchive(UI* ui_variable, char* pointer_to_separate);
void uiPrintAll(UI* ui_variable);
void uiPrintFilteredByType(UI* ui_variable, char fileType[]);
void uiPrintFilteredByYear(UI* ui_variable, char* pointer_to_separate);
void uiUndo(UI* ui_variable);
void uiRedo(UI* ui_variable);
void menu(UI* ui_variable);
void destroyUI(UI* ui_variable);
