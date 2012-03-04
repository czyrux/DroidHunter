#include <QtGui/QApplication>
#include "mainwindow.h"
#include "ventana.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Ventana ventana;
    ventana.show();
    
    return a.exec();
}
