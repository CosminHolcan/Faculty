#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include "Service.h"
#include <QtCharts/QChartView>
#include <QShortCut>
#include "mylistTableWidget.h"

class GUI : public QMainWindow
{
    Q_OBJECT

public:
	GUI(Service& service, QWidget* parent = Q_NULLPTR);

private:
	Ui::GUIClass ui;
	Service& service;
	void populateAll();
	void populateFiltered(std::vector<Victim> victims);
	void connectingSignals();
	int getSelectedIndexModeA();
	void guiSelectModeA();
	int getSelectedIndexModeB();
	void guiSelectModeB();
	void guiAddVictim();
	void guiDeleteVictim();
	void guiUpdateVictim();
	void guiUndoModeA();
	void guiRedoModeA();
	void guiUndoModeB();
	void guiRedoModeB();
	void guiFilter();
	void populateMylist();
	void guiSave();
	void guiNext();
	void runMylist();
	QtCharts::QChartView* createChart();
	void displayChart();
	QShortcut* shortcutUndoModeA;
	QShortcut* shortcutRedoModeA;
	QShortcut* shortcutUndoModeB;
	QShortcut* shortcutRedoModeB;
	void showMylistTableView();
};
