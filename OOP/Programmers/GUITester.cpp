#include "GUITester.h"

using namespace std;

GUITester::GUITester(Service& service, User user, QWidget *parent)
	: service(service),user(user), QWidget(parent)
{
	ui.setupUi(this);
	this->connectingSignals();
	this->populateAll();
	this->setWindowTitle(QString::fromStdString(this->user.print()));
}

GUITester::~GUITester()
{
}

void GUITester::connectingSignals()
{
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &GUITester::add);
	QObject::connect(this->ui.removeButton, &QPushButton::clicked, this, &GUITester::remove);
}

int GUITester::getSelectedIndex()
{
	QModelIndexList allIndexes = this->ui.issuesListWidget->selectionModel()->selectedIndexes();
	if (allIndexes.size() < 0)
		return -1;
	int selectedIndex = allIndexes.at(0).row();
	return selectedIndex;
}

void GUITester::populateAll()
{
	this->ui.issuesListWidget->clear();
	vector<Issue> issues = this->service.getAllIssuesSorted();
	for (auto issue : issues)
	{
		this->ui.issuesListWidget->addItem(QString::fromStdString(issue.print()));
	}
}

void GUITester::remove()
{
	int index = this->getSelectedIndex();
	if (index < 0)
		return;
	vector<Issue> issues = this->service.getAllIssuesSorted();
	Issue issue = issues[index];
	if (issue.getStatus() == "closed")
		this->service.removeIssue(issue.getDescription());
}

void GUITester::add()
{
	string description = this->ui.descriptionLineEdit->text().toStdString();
	this->service.addIssue(description, "open", this->user.getName(), "None");
}

void GUITester::update()
{
	this->populateAll();
}
