#include "GUI.h"
#include <qmessagebox.h>
#include <Windows.h>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieLegendMarker>

QT_CHARTS_USE_NAMESPACE

GUI::GUI(Service& service, QWidget* parent)
	: QMainWindow(parent), service{ service }
{
	ui.setupUi(this);
	this->shortcutUndoModeA = new QShortcut(QKeySequence("Ctrl+Z"), this->ui.ModeA);
	this->shortcutRedoModeA = new QShortcut(QKeySequence("Ctrl+Y"), this->ui.ModeA);
	this->shortcutUndoModeB = new QShortcut(QKeySequence("Ctrl+Z"), this->ui.ModeB);
	this->shortcutRedoModeB = new QShortcut(QKeySequence("Ctrl+Y"), this->ui.ModeB);
	this->connectingSignals();
	this->showMylistTableView();
}

void GUI::populateAll()
{
	this->ui.victimsListWidget->clear();
	std::vector<Victim> victims = this->service.serviceGetVictims();
	for (auto victim : victims)
	{
		/*
		QListWidgetItem* element = new QListWidgetItem(QString::fromStdString(victim.getName()), this->ui.victimsListWidget);
		QFont font = element->font();
		font.setBold(true);
		element->setFont(font);
		this->ui.victimsListWidget->addItem(element);
		*/
		this->ui.victimsListWidget->addItem(QString::fromStdString(victim.getName()));
	}
}

void GUI::populateFiltered(std::vector<Victim> victims)
{
	this->ui.victimsListWidget->clear();
	for (auto victim : victims)
	{
		this->ui.victimsListWidget->addItem(QString::fromStdString(victim.getName()));
	}
}

void GUI::connectingSignals()
{
	QObject::connect(this->ui.victimsListWidget, &QListWidget::itemSelectionChanged, this, &GUI::guiSelectModeA);
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &GUI::guiAddVictim);
	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &GUI::guiUpdateVictim);
	QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &GUI::guiDeleteVictim);
	QObject::connect(this->ui.filterButton, &QPushButton::clicked, this, &GUI::guiFilter);
	QObject::connect(this->ui.showButton, &QPushButton::clicked, this, &GUI::populateAll);
	QObject::connect(this->ui.mylistWidget, &QListWidget::itemSelectionChanged, this, &GUI::guiSelectModeB);
	QObject::connect(this->ui.saveButton, &QPushButton::clicked, this, &GUI::guiSave);
	QObject::connect(this->ui.nextButton, &QPushButton::clicked, this, &GUI::guiNext);
	QObject::connect(this->ui.allMylistButton, &QPushButton::clicked, this, &GUI::populateMylist);
	QObject::connect(this->ui.runButton, &QPushButton::clicked, this, &GUI::runMylist);
	QObject::connect(this->ui.chartButton, &QPushButton::clicked, this, &GUI::displayChart);
	QObject::connect(this->ui.undoButton, &QPushButton::clicked, this, &GUI::guiUndoModeA);
	QObject::connect(this->ui.redoButton, &QPushButton::clicked, this, &GUI::guiRedoModeA);
	QObject::connect(this->shortcutUndoModeA, &QShortcut::activated, this, &GUI::guiUndoModeA);
	QObject::connect(this->shortcutRedoModeA, &QShortcut::activated, this, &GUI::guiRedoModeA);
	QObject::connect(this->shortcutUndoModeB, &QShortcut::activated, this, &GUI::guiUndoModeB);
	QObject::connect(this->shortcutRedoModeB, &QShortcut::activated, this, &GUI::guiRedoModeB);
	QObject::connect(this->ui.tableModeButton, &QPushButton::clicked, this, &GUI::showMylistTableView);
	QObject::connect(this->ui.undoMylistButton, &QPushButton::clicked, this, &GUI::guiUndoModeB);
	QObject::connect(this->ui.redoMylistButton, &QPushButton::clicked, this, &GUI::guiRedoModeB);
}

int GUI::getSelectedIndexModeA()
{
	QModelIndexList allIndexes = this->ui.victimsListWidget->selectionModel()->selectedIndexes();
	if (allIndexes.size() == 0)
	{
		this->ui.nameLineEdit->clear();
		this->ui.placeLineEdit->clear();
		this->ui.ageLineEdit->clear();
		this->ui.photoLineEdit->clear();
		return -1;
	}
	int selectedIndex = allIndexes.at(0).row();
	return selectedIndex;
}

void GUI::guiSelectModeA()
{
	int indexSelectedVictim = this->getSelectedIndexModeA();
	if (indexSelectedVictim < 0)
		return;
	Victim victim = this->service.serviceGetVictims()[indexSelectedVictim];
	this->ui.nameLineEdit->setText(QString::fromStdString(victim.getName()));
	this->ui.placeLineEdit->setText(QString::fromStdString(victim.getPlaceOfOrigin()));
	this->ui.ageLineEdit->setText(QString::fromStdString(to_string(victim.getAge())));
	this->ui.photoLineEdit->setText(QString::fromStdString(victim.getPhotograph()));
}

int GUI::getSelectedIndexModeB()
{
	QModelIndexList allIndexes = this->ui.mylistWidget->selectionModel()->selectedIndexes();
	if (allIndexes.size() == 0)
	{
		this->ui.nameMylistlineEdit->clear();
		this->ui.placeMylistlineEdit->clear();
		this->ui.ageMylistlineEdit->clear();
		this->ui.photoMylistlineEdit->clear();
		return -1;
	}
	int selectedIndex = allIndexes.at(0).row();
	return selectedIndex;
}

void GUI::guiSelectModeB()
{
	int indexSelectedVictim = this->getSelectedIndexModeB();
	if (indexSelectedVictim < 0)
		return;
	Victim victim = this->service.serviceGetVictimsMylist()[indexSelectedVictim];
	this->ui.nameMylistlineEdit->setText(QString::fromStdString(victim.getName()));
	this->ui.placeMylistlineEdit->setText(QString::fromStdString(victim.getPlaceOfOrigin()));
	this->ui.ageMylistlineEdit->setText(QString::fromStdString(to_string(victim.getAge())));
	this->ui.photoMylistlineEdit->setText(QString::fromStdString(victim.getPhotograph()));
}

void GUI::guiAddVictim()
{
	try
	{
		string name = this->ui.nameLineEdit->text().toStdString();
		string place = this->ui.placeLineEdit->text().toStdString();
		int age = stoi(this->ui.ageLineEdit->text().toStdString());
		string photograph = this->ui.photoLineEdit->text().toStdString();
		this->service.serviceAddVictim(name, place, age, photograph);
		this->populateAll();
	}
	catch (RepositoryException& exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.getMessage()));
	}
	catch (...)
	{
		QMessageBox::critical(this, "Error", "These arguments are not valid ! ");
	}
	this->ui.nameLineEdit->clear();
	this->ui.placeLineEdit->clear();
	this->ui.ageLineEdit->clear();
	this->ui.photoLineEdit->clear();
	this->populateAll();
}

void GUI::guiDeleteVictim()
{
	int indexSelectedVictim = this->getSelectedIndexModeA();
	if (indexSelectedVictim < 0)
	{
		QMessageBox::critical(this, "Error", "No victim was selected !");
		return;
	}
	Victim victim = this->service.serviceGetVictims()[indexSelectedVictim];
	this->service.serviceDeleteVictim(victim.getName());
	this->populateAll();
}

void GUI::guiUpdateVictim()
{
	try
	{
		string name = this->ui.nameLineEdit->text().toStdString();
		string place = this->ui.placeLineEdit->text().toStdString();
		int age = stoi(this->ui.ageLineEdit->text().toStdString());
		string photograph = this->ui.photoLineEdit->text().toStdString();
		this->service.serviceUpdateVictim(name, place, age, photograph);
		this->populateAll();
	}
	catch (RepositoryException& exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.getMessage()));
	}
	catch (...)
	{
		QMessageBox::critical(this, "Error", "These arguments are not valid ! ");
	}
	this->ui.nameLineEdit->clear();
	this->ui.placeLineEdit->clear();
	this->ui.ageLineEdit->clear();
	this->ui.photoLineEdit->clear();
	this->populateAll();
}

void GUI::guiUndoModeA()
{
	try
	{
		this->service.serviceUndoRepository();
		this->populateAll();
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void GUI::guiRedoModeA()
{
	try
	{
		this->service.serviceRedoRepository();
		this->populateAll();
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void GUI::guiUndoModeB()
{
	try
	{
		this->service.serviceUndoMylist();
		this->populateMylist();
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void GUI::guiRedoModeB()
{
	try
	{
		this->service.serviceRedoMylist();
		this->populateMylist();
	}
	catch (exception& exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
	}
}

void GUI::guiFilter()
{
	if (this->ui.ageLineEdit->text().isEmpty())
		QMessageBox::critical(this, "Error", "These arguments are invalid !");
	else
	{
		try
		{
			int age = stoi(this->ui.ageLineEdit->text().toStdString());
			if (this->ui.placeLineEdit->text().isEmpty())
			{
				std::vector<Victim> victims = this->service.serviceGetFilteredWithoutPlace(age);
				this->populateFiltered(victims);
			}
			else
			{
				string place = this->ui.placeLineEdit->text().toStdString();
				std::vector<Victim> victims = this->service.serviceGetFilteredWithPlace(place, age);
				this->populateFiltered(victims);
			}
		}
		catch (...)
		{
			QMessageBox::critical(this, "Error", "These arguments are invalid !");
			return;
		}
	}
}

void GUI::populateMylist()
{
	std::vector<Victim> victims = this->service.serviceGetVictimsMylist();
	this->ui.mylistWidget->clear();
	for (auto victim : victims)
	{
		this->ui.mylistWidget->addItem(QString::fromStdString(victim.getName()));
	}
	this->ui.nameMylistlineEdit->clear();
	this->ui.placeMylistlineEdit->clear();
	this->ui.ageMylistlineEdit->clear();
	this->ui.photoMylistlineEdit->clear();
}

void GUI::guiSave()
{
	if (this->ui.nameMylistlineEdit->text().isEmpty())
		QMessageBox::critical(this, "Error", "These arguments are invalid !");
	else
	{
		try
		{
			std::string name = this->ui.nameMylistlineEdit->text().toStdString();
			this->service.serviceSaveVictim(name);
			this->populateMylist();
		}
		catch (RepositoryException& exception)
		{
			QMessageBox::critical(this, "Error", QString::fromStdString(exception.getMessage()));
		}
	}
	this->ui.nameMylistlineEdit->clear();
	this->ui.placeMylistlineEdit->clear();
	this->ui.ageMylistlineEdit->clear();
	this->ui.photoMylistlineEdit->clear();
}

void GUI::guiNext()
{
	this->ui.nameMylistlineEdit->clear();
	this->ui.placeMylistlineEdit->clear();
	this->ui.ageMylistlineEdit->clear();
	this->ui.photoMylistlineEdit->clear();
	Victim victim = this->service.serviceNext();
	this->ui.mylistWidget->clear();
	this->ui.mylistWidget->addItem(QString::fromStdString(victim.getName()));
	this->ui.nameMylistlineEdit->setText(QString::fromStdString(victim.getName()));
	this->ui.placeMylistlineEdit->setText(QString::fromStdString(victim.getPlaceOfOrigin()));
	this->ui.ageMylistlineEdit->setText(QString::fromStdString(to_string(victim.getAge())));
	this->ui.photoMylistlineEdit->setText(QString::fromStdString(victim.getPhotograph()));
}


void GUI::runMylist()
{
	std::string fileName = this->service.serviceGetFileMyList();
	if (fileName.find(".csv") != string::npos)
	{
		std::string commandAsString = "notepad.exe ";
		commandAsString = commandAsString + fileName;
		const char* cmd = commandAsString.c_str();
		system(cmd);
	}
	if (fileName.find(".html") != string::npos)
	{
		std::string commandAsString = "start chrome ";
		commandAsString = commandAsString + fileName;
		const char* cmd = commandAsString.c_str();
		system(cmd);
	}
}

QtCharts::QChartView* GUI::createChart()
{
	QPieSeries* seriesVictims = new QPieSeries();
	std::vector<Victim> victims = this->service.serviceGetVictims();
	int index = 0;
	for (auto victim : victims) {
		seriesVictims->append(QString::fromStdString("Name: " + victim.getName() + "  Age: " + std::to_string(victim.getAge()) + "\n"), victim.getAge());
		index++;
	}
	seriesVictims->setLabelsVisible();
	seriesVictims->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
	QChart* chart = new QChart();
	chart->addSeries(seriesVictims);
	chart->setTitle("Victims from Repository by age");
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignLeft);
	QList<QLegendMarker*> listOfLegendMarkers = chart->legend()->markers(seriesVictims);
	for (QLegendMarker* victimLegendMarker : listOfLegendMarkers)
	{
		QPieLegendMarker* victimPieMarkerInTheLegend = qobject_cast<QPieLegendMarker*>(victimLegendMarker);
		{
			victimPieMarkerInTheLegend->setLabel(QString("%1").arg(victimPieMarkerInTheLegend->slice()->label()));
		}
	}
	for (QPieSlice* evidenceSlice : seriesVictims->slices())
	{
		evidenceSlice->setLabelBrush(QBrush(Qt::white));
		evidenceSlice->setLabel(QString::number(evidenceSlice->percentage() * 100, 'f', 1) + "%");
	}
	QChartView* chartView = new QChartView(chart);
	return chartView;
}

void GUI::displayChart()
{
	QChartView* chartView = this->createChart();

	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->resize(600, 400);
	chartView->show();
}

void GUI::showMylistTableView()
{
	VictimsTableModel* model = new VictimsTableModel(this->service);
	mylistTableWidget* victimsTable = new mylistTableWidget(this->service, model);
	victimsTable->setWindowTitle("My list");
	this->service.addObserver(victimsTable);
	victimsTable->show();
}
