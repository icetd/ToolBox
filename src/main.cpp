#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "SqlManager.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    SqlManager::getInstance()->init();
    MainWindow w;
    w.show();
    return a.exec();
}
