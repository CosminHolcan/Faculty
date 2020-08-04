#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Tests.h"
#include "Service.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

void test_getArchiveCatalogueNumber_validArchive_ArchiveCatalogueNumber()
{
	Archive* archive = createArchive(123, "abc", "def", 456);
	assert(getArchiveCatalogueNumber(archive) == 123);
	destroyArchive(archive);
	_CrtDumpMemoryLeaks();
}

void test_getStateOfDeterioration_validArchive_StateOfDeterioration()
{
	Archive* archive = createArchive(123, "abc", "def", 456);
	assert(strcmp(getStateOfDeterioration(archive), "abc") == 0);
	destroyArchive(archive);
	_CrtDumpMemoryLeaks();
}

void test_getFileType_validArchive_FileType()
{
	Archive* archive = createArchive(123, "abc", "def", 456);
	assert(strcmp(getFileType(archive), "def") == 0);
	destroyArchive(archive);
	_CrtDumpMemoryLeaks();
}

void test_getYearOfCreation_YearOfCreation()
{
	Archive* archive = createArchive(123, "abc", "def", 456);
	assert(getYearOfCreation(archive) == 456);
	destroyArchive(archive);
	_CrtDumpMemoryLeaks();
}

void test_createCopyArchive_validArchive_anotherArchiveWithSameAttributes()
{
	Archive* archive = createArchive(123, "abc", "def", 456);
	Archive* copyArchive = createCopyArchive(archive);
	assert(getYearOfCreation(archive) == getYearOfCreation(copyArchive));
	destroyArchive(archive);
	destroyArchive(copyArchive);
	_CrtDumpMemoryLeaks();
}


void test_operationGetArchiveRedo_validOperation_ArchiveRedo()
{
	Archive* archiveRedo = createArchive(123, "abc", "def", 456);
	Archive* archiveUndo = createArchive(126, "abcd", "desf", 406);
	Operation* operation = createOperation(archiveRedo, archiveUndo, "add");
	Archive* archiveTest = operationGetArchiveRedo(operation);
	assert(archiveTest == archiveRedo);
	destroyOperation(operation);
	_CrtDumpMemoryLeaks();
}

void test_operationGetArchiveUndo_validOperation_ArchiveUndo()
{
	Archive* archiveRedo = createArchive(123, "abc", "def", 456);
	Archive* archiveUndo = createArchive(126, "abcd", "desf", 406);
	Operation* operation = createOperation(archiveRedo, archiveUndo, "add");
	Archive* archiveTest = operationGetArchiveUndo(operation);
	assert(archiveTest == archiveUndo);
	destroyOperation(operation);
	_CrtDumpMemoryLeaks();
}

void test_operationGetStringOperation_validOperation_StringOperation()
{
	Archive* archiveRedo = createArchive(123, "abc", "def", 456);
	Archive* archiveUndo = createArchive(126, "abcd", "desf", 406);
	Operation* operation = createOperation(archiveRedo, archiveUndo, "add");
	assert(strcmp(operationGetStringOperation(operation), "add") == 0);
	destroyOperation(operation);
	_CrtDumpMemoryLeaks();
}


void test_resizeArray_validArrayToResize_return0()
{
	DynamicArray* vector = createDynamicArray(1);
	Archive* archive = createArchive(123, "abc", "def", 100);
	addElementArray(vector, archive);
	int result = resizeArray(vector);
	assert(result == 0);
	destroyDynamicArrayOfArchives(vector);
	_CrtDumpMemoryLeaks();
}

void test_existArchiveArray_validArchive_return1()
{
	DynamicArray* vector = createDynamicArray(10);
	Archive* archive = createArchive(123, "abc", "def", 100);
	addElementArray(vector, archive);
	int result = existArchiveArray(vector, archive);
	assert(result == 1);
	destroyDynamicArrayOfArchives(vector);
	_CrtDumpMemoryLeaks();
}

void test_existArchiveArray_invalidArchive_return0()
{
	DynamicArray* vector = createDynamicArray(10);
	Archive* archive = createArchive(123, "abc", "def", 100);
	Archive* archive2 = createArchive(126, "abc", "def", 100);
	addElementArray(vector, archive);
	int result = existArchiveArray(vector, archive2);
	assert(result == 0);
	destroyDynamicArrayOfArchives(vector);
	destroyArchive(archive2);
	_CrtDumpMemoryLeaks();
}

void test_getPositionArchive_validArchive_position()
{
	DynamicArray* vector = createDynamicArray(10);
	Archive* archive = createArchive(123, "abc", "def", 100);
	addElementArray(vector, archive);
	int result = getPositionArchive(vector, archive);
	assert(result == 0);
	destroyDynamicArrayOfArchives(vector);
	_CrtDumpMemoryLeaks();
}

void test_getSizeArray_validArrayOfSize2_size2()
{
	DynamicArray* vector = createDynamicArray(10);
	Archive* archive = createArchive(123, "abc", "def", 100);
	Archive* archive2 = createArchive(126, "abc", "def", 100);
	addElementArray(vector, archive);
	addElementArray(vector, archive2);
	int result = getSizeArray(vector);
	assert(result == 2);
	destroyDynamicArrayOfArchives(vector);
	_CrtDumpMemoryLeaks();
}

void test_repositoryAddArchive_validArchive_return1()
{
	Repository* repository = createRepository();
	Archive* archive = createArchive(123, "abc", "def", 456);
	int result = repositoryAddArchive(repository, archive);
	assert(result == 1);
	destroyRepository(repository);
	_CrtDumpMemoryLeaks();
}

void test_repositoryAddArchive_duplicatedArchive_return0()
{
	Repository* repository = createRepository();
	Archive* archive = createArchive(123, "abc", "def", 456);
	Archive* archive2 = createArchive(123, "adbc", "dgref", 46);
	int result = repositoryAddArchive(repository, archive);
	result = repositoryAddArchive(repository, archive2);
	assert(result == 0);
	destroyRepository(repository);
	destroyArchive(archive2);
	_CrtDumpMemoryLeaks();
}

void test_repositoryUpdateArchive_validArchive_return1()
{
	Repository* repository = createRepository();
	Archive* archive = createArchive(123, "abc", "def", 456);
	Archive* archive2 = createArchive(123, "abcfe", "dfdef", 40556);
	int result = repositoryAddArchive(repository, archive);
	result = repositoryUpdateArchive(repository, archive2);
	assert(result == 1);
	destroyRepository(repository);
	_CrtDumpMemoryLeaks();
}

void test_repositoryUpdateArchive_invalidArchive_return0()
{
	Repository* repository = createRepository();
	Archive* archive = createArchive(123, "abc", "def", 456);
	Archive* archive2 = createArchive(1234, "abcfe", "dfdef", 40556);
	int result = repositoryAddArchive(repository, archive);
	result = repositoryUpdateArchive(repository, archive2);
	assert(result == 0);
	destroyRepository(repository);
	destroyArchive(archive2);
	_CrtDumpMemoryLeaks();
}

void test_serviceAddArchive_validArchive_return1()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	int result = serviceAddArchive(service, 123, "abc", "def", 100);
	assert(result == 1);
	destroyService(service);
	_CrtDumpMemoryLeaks();
}

void test_serviceAddArchive_duplicatedArchive_return0()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	int result = serviceAddArchive(service, 123, "abc", "def", 100);
	result = serviceAddArchive(service, 123, "de", "deef", 15);
	assert(result == 0);
	destroyService(service);
	_CrtDumpMemoryLeaks();
}

void test_serviceDeleteArchive_validArchive_return1()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	int result = serviceAddArchive(service, 123, "abc", "def", 100);
	result = serviceDeleteArchive(service, 123);
	assert(result == 1);
	destroyService(service);
	_CrtDumpMemoryLeaks();
}

void test_serviceDeleteArchive_inexistentArchive_return0()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	int result = serviceAddArchive(service, 123, "abc", "def", 100);
	result = serviceDeleteArchive(service, 124);
	assert(result == 0);
	destroyService(service);
	_CrtDumpMemoryLeaks();
}

void test_serviceUndo_validUndo_return1()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	int result = serviceAddArchive(service, 123, "abc", "def", 100);
	result = serviceAddArchive(service, 125, "abdsc", "deffe", 10);
	result = serviceUndo(service);
	assert(result == 1);
	destroyService(service);
	_CrtDumpMemoryLeaks();
}

void test_serviceUndo_invalidUndo_return0()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	int result = serviceUndo(service);
	assert(result == 0);
	destroyService(service);
	_CrtDumpMemoryLeaks();
}

void test_serviceRedo_validRedo_return1()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	int result = serviceAddArchive(service, 123, "abc", "def", 100);
	result = serviceAddArchive(service, 125, "abdsc", "deffe", 10);
	result = serviceUndo(service);
	result = serviceRedo(service);
	assert(result == 1);
	destroyService(service);
	_CrtDumpMemoryLeaks();
}

void test_serviceRedo_invalidRedo_return0()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	int result = serviceAddArchive(service, 123, "abc", "def", 100);
	result = serviceAddArchive(service, 125, "abdsc", "deffe", 10);
	result = serviceRedo(service);
	assert(result == 0);
	destroyService(service);
	_CrtDumpMemoryLeaks();
}

void testAll()
{
	
	test_getArchiveCatalogueNumber_validArchive_ArchiveCatalogueNumber();
	test_getStateOfDeterioration_validArchive_StateOfDeterioration();
	test_getFileType_validArchive_FileType();
	test_getYearOfCreation_YearOfCreation();
	test_createCopyArchive_validArchive_anotherArchiveWithSameAttributes();
	test_operationGetArchiveRedo_validOperation_ArchiveRedo();
	test_operationGetArchiveUndo_validOperation_ArchiveUndo();
	test_operationGetStringOperation_validOperation_StringOperation();
	test_resizeArray_validArrayToResize_return0();
	test_existArchiveArray_validArchive_return1();
	test_existArchiveArray_invalidArchive_return0();
	test_getPositionArchive_validArchive_position();
	test_getSizeArray_validArrayOfSize2_size2();
	test_repositoryAddArchive_validArchive_return1();
	test_repositoryAddArchive_duplicatedArchive_return0();
	test_repositoryUpdateArchive_validArchive_return1();
	test_repositoryUpdateArchive_invalidArchive_return0();
	test_serviceAddArchive_validArchive_return1();
	test_serviceAddArchive_duplicatedArchive_return0();
	test_serviceDeleteArchive_validArchive_return1();
	test_serviceDeleteArchive_inexistentArchive_return0();
	test_serviceUndo_validUndo_return1();
	test_serviceUndo_invalidUndo_return0();
	test_serviceRedo_validRedo_return1();
	test_serviceRedo_invalidRedo_return0();
	
}

