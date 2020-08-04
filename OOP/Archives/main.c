#include "UI.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include "Tests.h"

int main()
{
	testAll();
	Repository* repository = createRepository();
	Service* service = createService(repository);
	UI* ui_variable = createUI(service);
	menu(ui_variable);
	destroyUI(ui_variable);
	_CrtDumpMemoryLeaks();
	return 0;
}