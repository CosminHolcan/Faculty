#include "mylistTableWidget.h"

mylistTableWidget::mylistTableWidget(Service& service, VictimsTableModel* model, QWidget* parent)
	: QWidget(parent), model(model), service(service)
{
	ui.setupUi(this);
	this->ui.victimsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	this->ui.victimsTableView->setModel(this->model);
	this->ui.victimsTableView->setItemDelegate(new PictureDelegate());
	this->ui.victimsTableView->resizeColumnsToContents();
	this->ui.victimsTableView->resizeRowsToContents();

}

void mylistTableWidget::update()
{
	VictimsTableModel* newModel = new VictimsTableModel(this->service);
	this->ui.victimsTableView->setModel(newModel);
	this->ui.victimsTableView->resizeColumnsToContents();
	this->ui.victimsTableView->resizeRowsToContents();
	this->ui.victimsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


mylistTableWidget::~mylistTableWidget()
{
}

