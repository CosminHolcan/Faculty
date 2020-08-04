#pragma once

#include <QWidget>
#include "ui_GUITester.h"
#include "Service.h"
#include "Observer.h"

class GUITester : public QWidget, public Observer
{
	Q_OBJECT

public:
	GUITester(Service& service, User user, QWidget* parent = Q_NULLPTR);
	~GUITester();

private:
	Ui::GUITester ui;
	Service& service;
	User user;
	void connectingSignals();
	int getSelectedIndex();
	void populateAll();
	void remove();
	void add();
	void update() override;
};
