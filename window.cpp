 #include <QtGui>
#include <QPushButton>

 #include "window.h"

 Window::Window()
 {
     visorOpenGL = new VisorOpenGL;

     QHBoxLayout *mainLayout = new QHBoxLayout;
     mainLayout->addWidget(this->visorOpenGL);
     setLayout(mainLayout);
     setWindowTitle(tr("IG[2010-...]. czyrux"));
     //resize(1280,800);
     resize(1000,800);

 }


void Window::keyPressEvent(QKeyEvent *event){
}
