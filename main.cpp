#include <QApplication>
#include <QPushButton>
#include "tests.h"
#include "GUI.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    tests::testAll();
    Repo repo{"date.txt"};
    Service service {repo};
    GUI gui{service};
    gui.show();
    return QApplication::exec();
}
