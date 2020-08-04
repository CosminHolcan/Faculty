#pragma once
#include "Repository.h"

#include <QWidget>
#include "ui_Manager.h"

class Manager : public QWidget
{
	Q_OBJECT

public:
	Manager(Repository& repository, QWidget *parent = Q_NULLPTR);
	~Manager();

private:
	Ui::Manager ui;
	Repository& repository;
	void populateAll();
	void connectingSignals();
	void showDuration();
};
