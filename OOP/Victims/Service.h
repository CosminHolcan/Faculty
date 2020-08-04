#pragma once
#include "Repository.h"
#include "InFileRepository.h"
#include <memory>
#include "Operation.h"
#include <exception>
#include "Observer.h"

using namespace std;

class Service : public Subject
{
private:
	shared_ptr<Repository> repository;
	shared_ptr<Repository> mylist;
	vector<shared_ptr<Operation>> operationsUndoRepository;
	vector<shared_ptr<Operation>> operationsRedoRepository;
	vector<shared_ptr<Operation>> operationsUndoMylist;
	vector<shared_ptr<Operation>> operationsRedoMylist;
public:
	Service(shared_ptr<Repository> repository, shared_ptr<Repository> mylist) : repository{ repository }, mylist{mylist} {}
	std::vector<Victim> serviceGetVictims() const;
	bool serviceAddVictim(const std::string& name, const std::string& placeOfOrigin, int age, const std::string& photograph);
	bool serviceDeleteVictim(const std::string& name);
	bool serviceUpdateVictim(const std::string& name, const std::string& placeOfOrigin, int age, const std::string& photograph);
	void serviceUndoRepository();
	void serviceRedoRepository();
	Victim serviceNext() const;
	bool serviceSaveVictim(const std::string& name);
	void serviceUndoMylist();
	void serviceRedoMylist();
	std::vector<Victim> serviceGetFilteredWithPlace(const std::string& placeOfOrigin, int age);
	std::vector<Victim> serviceGetFilteredWithoutPlace(int age);
	void serviceSetFileInRepository(std::string nameOfFile);
	void serviceSetFileMyList(std::string nameOfFile);
	std::vector<Victim> serviceGetVictimsMylist();
	std::string serviceGetFileMyList();
	~Service();
};
