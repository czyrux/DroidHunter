#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include "visoropengl.h"

 class Ventana : public QWidget
 {
 public:
     Ventana();
     void keyPressEvent(QKeyEvent *event);
 private:
     VisorOpenGL *visorOpenGL;

 };

 #endif


