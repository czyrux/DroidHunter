#include <QtGui/QApplication>
#include "mainwindow.h"
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Window _window;
    _window.show();
    
    return a.exec();
}
