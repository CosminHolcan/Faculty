#include "InFileRepository.h"

std::vector<Victim> readFromFile(std::string nameOfFile)
{
	ifstream file{ nameOfFile };
	vector<Victim> victims;
	Victim victim;
	while (file >> victim)
	{
		victims.push_back(victim);
	}
	file.close();
	return victims;
}

void writeToFile(std::string nameOfFile, const std::vector<Victim>& victims)
{
	ofstream file{ nameOfFile };
	for (Victim victim : victims)
	{
		file << victim;
	}
	file.close();
}

void writeToHTML(std::string fileName, const std::vector<Victim> victims)
{
	ofstream outputFile{ fileName };
	outputFile << "<!DOCTYPE html>" << '\n' << "<html>" << '\n' << "<head>" << '\n' << "<title>MyList</title>" << '\n' << "</head>" << '\n'
		<< "<body>" << '\n' << "<table border=\"1\">" << '\n' << "<tr>" << '\n' << "<td>Name</td>" << '\n' << "<td>Place</td>" <<
		'\n' << "<td>Age</td>" << '\n' << "<td>Photograph</td>" << '\n' << "</tr>" << '\n';
	for (Victim victim : victims)
	{
		std::string name = victim.getName();
		std::string place = victim.getPlaceOfOrigin();
		int age = victim.getAge();
		std::string photograph = victim.getPhotograph();
		outputFile << "<tr>\n" << "<td>\n" << name << "\n</td>\n" << "<td>\n" << place << "\n</td>\n" << "<td>\n" << age << "\n</td>\n"
			<< "<td>\n" << photograph << "\n</td>\n" << "</tr>\n";
	}
	outputFile << "</table>" << '\n' << "</body>" << '\n' << "</html>";
	outputFile.close();
}


std::vector<Victim> readFromHTML(std::string fileName)
{
	ifstream file{ fileName };
	vector<Victim> victimsToReturn;
	vector<string> lines;
	string line;
	while (std::getline(file, line))
		lines.push_back(line);
	if (lines.size() < 17)
		return victimsToReturn;
	for (size_t index = 15; index < lines.size() - 3; index = index + 14)
	{
		string name, place, photograph;
		int age;
		name = lines[index];
		place = lines[index + 3];
		age = stoi(lines[index + 6]);
		photograph = lines[index + 9];
		Victim victim{ name, place, age, photograph };
		victimsToReturn.push_back(victim);
	}
	return victimsToReturn;
}


bool InFileRepository::repositoryAddVictim(const Victim& victim)
{
	vector<Victim> victims;
	if (this->fileName.find(".txt") != std::string::npos || this->fileName.find(".csv") != std::string::npos)
		victims = readFromFile(this->fileName);
	if (this->fileName.find(".html") != std::string::npos)
		victims = readFromHTML(this->fileName);
	if (std::find(victims.begin(), victims.end(), victim) == victims.end())
	{
		victims.push_back(victim);
		if (this->fileName.find(".txt") != std::string::npos || this->fileName.find(".csv") != std::string::npos)
			writeToFile(this->fileName, victims);
		if (this->fileName.find(".html") != std::string::npos)
			writeToHTML(this->fileName, victims);
		return true;
	}
	else
		throw RepositoryException("This victim is already in repository !");
}

bool InFileRepository::repositoryDeleteVictim(const Victim& victim)
{
	vector<Victim> victims;
	if (this->fileName.find(".txt") != std::string::npos || this->fileName.find(".csv") != std::string::npos)
		victims = readFromFile(this->fileName);
	if (this->fileName.find(".html") != std::string::npos)
		victims = readFromHTML(this->fileName);
	if (std::find(victims.begin(), victims.end(), victim) != victims.end())
	{
		victims.erase(std::remove(victims.begin(), victims.end(), victim), victims.end());
		if (this->fileName.find(".txt") != std::string::npos || this->fileName.find(".csv") != std::string::npos)
			writeToFile(this->fileName, victims);
		if (this->fileName.find(".html") != std::string::npos)
			writeToHTML(this->fileName, victims);
		return true;
	}
	else
		throw RepositoryException("This victim is not in repository !");
}

bool InFileRepository::repositoryUpdateVictim(const Victim& victim)
{
	vector<Victim> victims;
	if (this->fileName.find(".txt") != std::string::npos || this->fileName.find(".csv") != std::string::npos)
		victims = readFromFile(this->fileName);
	if (this->fileName.find(".html") != std::string::npos)
		victims = readFromHTML(this->fileName);
	if (std::find(victims.begin(), victims.end(), victim) != victims.end())
	{
		victims.erase(std::remove(victims.begin(), victims.end(), victim), victims.end());
		victims.push_back(victim);
		if (this->fileName.find(".txt") != std::string::npos || this->fileName.find(".csv") != std::string::npos)
			writeToFile(this->fileName, victims);
		if (this->fileName.find(".html") != std::string::npos)
			writeToHTML(this->fileName, victims);
		return true;
	}
	else
		throw RepositoryException("This victim is not in repository !");
}


std::vector<Victim> InFileRepository::repositoryGetAllVictims() const
{
	vector<Victim> victims;
	if (this->fileName.find(".txt") != std::string::npos || this->fileName.find(".csv") != std::string::npos)
		victims = readFromFile(this->fileName);
	if (this->fileName.find(".html") != std::string::npos)
		victims = readFromHTML(this->fileName);
	return victims;
}

Victim InFileRepository::repositoryGetVictim(const Victim& victim) const
{
	vector<Victim> victims;
	if (this->fileName.find(".txt") != std::string::npos || this->fileName.find(".csv") != std::string::npos)
		victims = readFromFile(this->fileName);
	if (this->fileName.find(".html") != std::string::npos)
		victims = readFromHTML(this->fileName);
	if (std::find(victims.begin(), victims.end(), victim) == victims.end())
		throw RepositoryException("This victim is not in repository !");
	for (Victim victimFromRepository : victims)
		if (victimFromRepository == victim)
			return victimFromRepository;
}

bool InFileRepository::repositoryExistVictim(const Victim& victim)
{
	vector<Victim> victims;
	if (this->fileName.find(".txt") != std::string::npos || this->fileName.find(".csv") != std::string::npos)
		victims = readFromFile(this->fileName);
	if (this->fileName.find(".html") != std::string::npos)
		victims = readFromHTML(this->fileName);
	for (Victim victimRepository : victims)
		if (victimRepository == victim)
			return true;
	return false;
}


Victim InFileRepository::repositoryNext()
{
	vector<Victim> victims;
	if (this->fileName.find(".txt") != std::string::npos || this->fileName.find(".csv") != std::string::npos)
		victims = readFromFile(this->fileName);
	if (this->fileName.find(".html") != std::string::npos)
		victims = readFromHTML(this->fileName);
	if (this->indexIterator >= victims.size())
		this->indexIterator = 0;
	return victims[this->indexIterator++];
}

void InFileRepository::setFileName(std::string nameOfFile)
{
	this->fileName = nameOfFile;
	this->indexIterator = 0;
	ifstream inputFile{ nameOfFile };
	if (nameOfFile.find(".html") != string::npos)
	{
		if (inputFile.peek() == std::ifstream::traits_type::eof())
		{
			inputFile.close();
			ofstream file{ nameOfFile };
			file << "<!DOCTYPE html>" << '\n' << "<html>" << '\n' << "<head>" << '\n' << "<title>MyList</title>" << '\n' << "</head>" << '\n'
				<< "<body>" << '\n' << "<table border=\"1\">" << '\n' << "<tr>" << '\n' << "<td>Name</td>" << '\n' << "<td>Place</td>" <<
				'\n' << "<td>Age</td>" << '\n' << "<td>Photograph</td>" << '\n' << "</tr>" << '\n';
			file << "</table>" << '\n' << "</body>" << '\n' << "</html>";
			file.close();
		}
		else
			inputFile.close();
	}
}

std::string InFileRepository::getFileName()
{
	return this->fileName;
}

