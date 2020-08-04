#include "Task_manager.h"
#include "Manager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repository("tasks.txt");
    Manager manager(repository);
    manager.show();
    return a.exec();
}
