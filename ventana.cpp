 #include <QtGui>
#include <QPushButton>

 #include "ventana.h"

 Ventana::Ventana()
 {
     visorOpenGL = new VisorOpenGL;

     QHBoxLayout *mainLayout = new QHBoxLayout;
     mainLayout->addWidget(this->visorOpenGL);
     setLayout(mainLayout);
     setWindowTitle(tr("IG:Proyecto [2010-2011]. Antonio Gutierrez Martinez"));
     resize(1280,800);
 }


void Ventana::keyPressEvent(QKeyEvent *event){
}
