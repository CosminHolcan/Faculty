#include "GUIProgrammer.h"

GUIProgrammer::GUIProgrammer(Service& service,User user,  QWidget* parent)
	: service(service),user(user), QWidget(parent)
{
	ui.setupUi(this);
	this->connectingSignals();
	this->populateAll();
	this->setWindowTitle(QString::fromStdString(this->user.print()));
}

GUIProgrammer::~GUIProgrammer()
{
}

void GUIProgrammer::connectingSignals()
{
	QObject::connect(this->ui.solveButton, &QPushButton::clicked, this, &GUIProgrammer::solve);
	QObject::connect(this->ui.removeButton, &QPushButton::clicked, this, &GUIProgrammer::solve);
}

int GUIProgrammer::getSelectedIndex()
{
	QModelIndexList allIndexes = this->ui.IssuesListWidget->selectionModel()->selectedIndexes();
	if (allIndexes.size() < 0)
		return -1;
	int selectedIndex = allIndexes.at(0).row();
	return selectedIndex;
}

void GUIProgrammer::populateAll()
{
	this->ui.IssuesListWidget->clear();
	vector<Issue> issues = this->service.getAllIssuesSorted();
	for (auto issue : issues)
	{
		this->ui.IssuesListWidget->addItem(QString::fromStdString(issue.print()));
	}
}

void GUIProgrammer::remove()
{
	int index = this->getSelectedIndex();
	if (index < 0)
		return;
	vector<Issue> issues = this->service.getAllIssuesSorted();
	Issue issue = issues[index];
	if (issue.getStatus() == "closed")
		this->service.removeIssue(issue.getDescription());
}

void GUIProgrammer::solve()
{
	int index = this->getSelectedIndex();
	if (index < 0)
		return;
	vector<Issue> issues = this->service.getAllIssuesSorted();
	Issue issue = issues[index];
	if (issue.getStatus() == "open")
		this->service.updateIssue(issue.getDescription(), "closed", issue.getReporter(), this->user.getName());
}

void GUIProgrammer::update()
{
	this->populateAll();
}
