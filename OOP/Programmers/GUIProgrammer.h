#pragma once

#include <QWidget>
#include "ui_GUIProgrammer.h"
#include "Service.h"
#include "Observer.h"

class GUIProgrammer : public QWidget, public Observer
{
	Q_OBJECT

public:
	GUIProgrammer(Service& service, User user, QWidget* parent = Q_NULLPTR);
	~GUIProgrammer();

private:
	Ui::GUIProgrammer ui;
	Service& service;
	User user;
	void connectingSignals();
	int getSelectedIndex();
	void populateAll();
	void remove();
	void solve();
	void update() override;
};
