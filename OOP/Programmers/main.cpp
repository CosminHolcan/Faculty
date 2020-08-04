#include "Practic2.h"
#include <QtWidgets/QApplication>
#include "GUIProgrammer.h"
#include "GUITester.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository<User> users("friends.txt");
    Repository<Issue> issues("issues.txt");
    Service service(users, issues);
    vector<GUITester*> testers;
    vector<GUIProgrammer*> programmers;
    for (auto user : users.getAll())
    {
        if (user.getType() == "tester")
        {
            GUITester* tester = new GUITester(service, user);
            testers.push_back(tester);
            service.addObserver(tester);
        }
        if (user.getType() == "programmer")
        {
            GUIProgrammer* prog = new GUIProgrammer(service, user);
            programmers.push_back(prog);
            service.addObserver(prog);
        }
    }
    for (auto tester : testers)
        tester->show();
    for (auto prog : programmers)
        prog->show();
    return a.exec();
}
