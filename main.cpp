#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //a.setAttribute(Qt::AA_X11InitThreads);
    return a.exec();
}
