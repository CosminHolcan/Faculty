#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "InFileRepository.h"
#include <fstream>

using namespace std;

vector<string> getFunctionAndParameters(std::string input)
{
	vector<string> vectorOfParameters;
	stringstream streamToGetParameters(input);
	string parameter;
	getline(streamToGetParameters, parameter, '=');
	vectorOfParameters.push_back(parameter);
	while (getline(streamToGetParameters, parameter, '\n'))
	{
		if (vectorOfParameters.size() != 1)
			parameter.erase(parameter.begin());
		vectorOfParameters.push_back(parameter);
	}
	return vectorOfParameters;
}

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	shared_ptr<Repository> repository, mylist;
	ifstream file("settingsFile.txt");
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<string> parameters = getFunctionAndParameters(line);
		if (parameters[0] == "repository")
			if (parameters[1] == "in memory")
				repository = make_shared<InMemoryRepository>();
			else
			{
				repository = make_shared<InFileRepository>();
				repository->setFileName(parameters[1]);
			}
		if (parameters[0] == "mylist")
			if (parameters[1] == "in memory")
				mylist = make_shared<InMemoryRepository>();
			else
			{
				mylist = make_shared<InFileRepository>();
				mylist->setFileName(parameters[1]);
			}
	}
	Service service(repository, mylist);
	GUI gui(service);
	gui.setWindowTitle("Morgue");
	gui.show();
	return a.exec();
}
