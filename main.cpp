#include "widget.h"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow mainWindow;
    Widget* w = new Widget;
    mainWindow.setCentralWidget(w);
    mainWindow.show();
    return a.exec();
}
