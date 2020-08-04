#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Practic2.h"

class Practic2 : public QMainWindow
{
    Q_OBJECT

public:
    Practic2(QWidget *parent = Q_NULLPTR);

private:
    Ui::Practic2Class ui;
};
