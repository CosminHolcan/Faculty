#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Task_manager.h"

class Task_manager : public QMainWindow
{
    Q_OBJECT

public:
    Task_manager(QWidget *parent = Q_NULLPTR);

private:
    Ui::Task_managerClass ui;
};
