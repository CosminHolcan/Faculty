#pragma once

#include <QWidget>
#include "Observer.h"
#include "Service.h"
#include "VictimsTableModel.h"
#include "ui_mylistTableWidget.h"
#include "PictureDelegate.h"

class mylistTableWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	mylistTableWidget(Service& service, VictimsTableModel* model, QWidget* parent = Q_NULLPTR);
	~mylistTableWidget();

private:
	Ui::mylistTableWidget ui;
	Service& service;
	VictimsTableModel* model;
	void update() override;
};