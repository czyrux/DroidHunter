 #include <QtGui>
#include <QPushButton>

 #include "ventana.h"

 Ventana::Ventana()
 {
     visorOpenGL = new VisorOpenGL;

     QHBoxLayout *mainLayout = new QHBoxLayout;
     mainLayout->addWidget(this->visorOpenGL);
     setLayout(mainLayout);
     setWindowTitle(tr("IG[2010-2011]. czyrux"));
     resize(1280,800);
 }


void Ventana::keyPressEvent(QKeyEvent *event){
}
