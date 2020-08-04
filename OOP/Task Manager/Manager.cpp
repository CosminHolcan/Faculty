#include "Manager.h"

using namespace std;

Manager::Manager(Repository& repository,QWidget *parent)
	: QWidget(parent), repository(repository)
{
	ui.setupUi(this);
	populateAll();
	connectingSignals();
}


void Manager::populateAll()
{
	this->ui.ManagerListWidget->clear();
	vector<Task> tasks = this->repository.readFromFile();
	for (Task task : tasks)
	{
		QListWidgetItem* element = new QListWidgetItem(QString::fromStdString(task.getDescription() + " | " + to_string(task.getPriority())));
		if (task.getPriority() == 1)
		{
			QFont font = element->font();
			font.setBold(true);
			element->setFont(font);
		}
		this->ui.ManagerListWidget->addItem(element);
	}

}

void Manager::connectingSignals()
{
	QObject::connect(this->ui.showDurationButton, &QPushButton::clicked, this, &Manager::showDuration);
}

void Manager::showDuration()
{
	int priority = stoi(this->ui.priorityLineEdit->text().toStdString());
	int duration = this->repository.totalDuration(priority);
	this->ui.durationLineEdit->setText(QString::fromStdString(to_string(duration)));
}

Manager::~Manager()
{
}
