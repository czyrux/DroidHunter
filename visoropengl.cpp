#include "visoropengl.h"
#include "iostream"
#include <math.h>
#include <QCoreApplication>

 VisorOpenGL::VisorOpenGL(QWidget *parent)
     : QGLWidget(parent) {

     // Definimos el tamaño del volumen de visualización
     Window_width=5;//5;
     Window_height=5;//5;
     Front_plane=10;
     Back_plane=1000;

     // permitimos al componente tener el foco y aceptar eventos
     setFocusPolicy(Qt::StrongFocus);

     //iniciamos las camaras
     Camera camera;

     //camara 1 frente
     this->VRP.x=200;this->VRP.y=100;this->VRP.z=00;
     this->VPN.x=1;this->VPN.y=1;this->VPN.z=0;
     this->VUP.x=0;this->VUP.y=1;this->VUP.z=0;
     camera.set(VRP,VPN,VUP);
     camera.rotateX(5);
     cameras.push_back(camera);

     /*this->VRP.x=0;this->VRP.y=0;this->VRP.z=100;
     this->VPN.x=0;this->VPN.y=0;this->VPN.z=1;
     this->VUP.x=0;this->VUP.y=0;this->VUP.z=-1;
     camera.set(VRP,VPN,VUP);
     cameras.push_back(camera);

     this->VRP.x=100;this->VRP.y=100;this->VRP.z=100;
     this->VPN.x=1;this->VPN.y=1;this->VPN.z=1;
     this->VUP.x=0;this->VUP.y=1;this->VUP.z=0;
     camera.set(VRP,VPN,VUP);
     //camera.rotateX(5);
     cameras.push_back(camera);*/

     //camara 2
     this->VRP.x=-250;this->VRP.y=200;this->VRP.z=280;
     this->VPN.x=1;this->VPN.y=1;this->VPN.z=0;
     this->VUP.x=0;this->VUP.y=1;this->VUP.z=0;
     camera.set(VRP,VPN,VUP);
     cameras.push_back(camera);


     //camara 3 lateral izq
     this->VRP.x=50;this->VRP.y=75;this->VRP.z=200;
     this->VPN.x=1;this->VPN.y=1;this->VPN.z=1;
     this->VUP.x=0;this->VUP.y=1;this->VUP.z=0;
     camera.set(VRP,VPN,VUP);
     camera.rotateX(5);
     camera.rotateY(5);
     cameras.push_back(camera);


     //camara 4 lateral drcho
     this->VRP.x=200;this->VRP.y=100;this->VRP.z=-200;
     this->VPN.x=1;this->VPN.y=1;this->VPN.z=0;
     this->VUP.x=0;this->VUP.y=1;this->VUP.z=0;
     camera.set(VRP,VPN,VUP);
     camera.rotateX(5);
     camera.rotateY(-10);
     cameras.push_back(camera);

     //camara 5 cam ajustable
     this->VRP.x=0;this->VRP.y=40;this->VRP.z=0;
     this->VPN.x=1;this->VPN.y=1;this->VPN.z=0;
     this->VUP.x=0;this->VUP.y=-1;this->VUP.z=0;
     camera.set(VRP,VPN,VUP);
     cameras.push_back(camera);

     //camara 6 gallery cam
     this->VRP.x=15;this->VRP.y=10;this->VRP.z=0;
     this->VPN.x=1;this->VPN.y=1;this->VPN.z=0;
     this->VUP.x=0;this->VUP.y=1;this->VUP.z=0;
     camera.set(VRP,VPN,VUP);
     camera.rotateX(15);
     cameras.push_back(camera);

     //definimos la camara a visualizar
     camera_actual = 0;
     ncameras = 5 ;

     _fog = true;
}

 VisorOpenGL::~VisorOpenGL() {
     makeCurrent();
     cameras.clear();
 }

 QSize VisorOpenGL::minimumSizeHint() const {
     return QSize(50, 50);
 }

 QSize VisorOpenGL::sizeHint() const {
    // return QSize(400, 400);
     return QSize(800, 800);
 }

void VisorOpenGL::normalizeAngle(float angle) {
     while (angle>360)
	     angle-=360;
     while (angle<0)
	     angle+=360;
}


void VisorOpenGL::initializeGL()  {
     glClearColor(1.0,1.0,1.0,1.0);
     glShadeModel(GL_FLAT);
     //glShadeModel(GL_SMOOTH);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     glEnable(GL_NORMALIZE);

     //Configurar signal idle
     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(idle()));
     timer->start();

     // Configurar niebla
     GLfloat density = 0.0020;
     density = 0.0016;//0.006;
     GLfloat fogColor[4] = {0.5f, 0.5f, 0.5f, 1.0f};
     glFogi (GL_FOG_MODE, GL_EXP2);
     glFogfv (GL_FOG_COLOR, fogColor);
     glFogf (GL_FOG_DENSITY, density);
     glHint (GL_FOG_HINT, GL_NICEST);
     glEnable (GL_FOG);
 }

void VisorOpenGL::disable_FOG(){
    glDisable(GL_FOG);
    _fog = false;
}

void VisorOpenGL::enable_FOG(){
    glEnable(GL_FOG);
    _fog = true;
}

 void VisorOpenGL::resizeGL(int width, int height)
 {
     //int side = qMin(width, height);
     //glViewport((width - side) / 2, (height - side) / 2, width,width);//side, side);
     glViewport(0,0,width,height);
     setProjection();
}

void VisorOpenGL::setProjection(){
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
     //glFrustum(-Window_width/2,Window_width/2,-Window_height/2,Window_height/2,Front_plane,Back_plane);
     glMatrixMode(GL_MODELVIEW);
 }

void VisorOpenGL::setCamara() {

    //Ajustes de camara
    /*if ( camera_actual == 2 ) {
        _vertex3f aux = ((Camera)cameras[camera_actual]).getVRP();
        cout << "antes " << aux.x << " " << aux.y << " " << aux.z << endl;
        _vertex3f posicion = escena.getCharacterPosition();
        aux = posicion;

        float spin = escena.getCharacterSpin();
        cout << "droid " << aux.x << " " << aux.y << " " << aux.z << ". giro: "<< spin << endl;

        this->VRP.x=posicion.x;this->VRP.y=10;this->VRP.z=posicion.z;
        this->VPN.x=0;this->VPN.y=0;this->VPN.z=1;
        this->VUP.x=0;this->VUP.y=1;this->VUP.z=0;
        ((Camera)cameras[camera_actual]).setVRP(VRP);
        //((Camera)cameras[camera_actual]).rotateX(90);
        //((Camera)cameras[camera_actual]).rotateZ(spin);
        //((Camera)cameras[camera_actual]).translateX(posicion.x);
        //((Camera)cameras[camera_actual]).translateZ(posicion.z);
        aux = ((Camera)cameras[camera_actual]).getVRP();
        cout << "despues " << aux.x << " " << aux.y << " " << aux.z << endl;
    }if ( camera_actual == 1 ) {

    }*/

    //Visualizacion de la camara
    /*if ( camera_actual == 1 )
        cameras[camera_actual].lookat(true);
    else*/
        cameras[camera_actual].lookat();
}


void VisorOpenGL::paintGL() {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     setProjection();
     setCamara();
     dibujarEscena();
 }

 void VisorOpenGL::idle() {
    _scene.animate();
    updateGL();
 }

void VisorOpenGL::keyPressEvent(QKeyEvent *event){

 switch( event->key() )   {
    //Seleccion de escena
    case Qt::Key_1: _scene.setScene(1);camera_actual = 0 ;break;
    case Qt::Key_2:_scene.setScene(2);camera_actual = ncameras;break;

    //Seleccion del modo de visualizacion
    case Qt::Key_3:_scene.setDrawMode(gouraud);break;
    case Qt::Key_4:_scene.setDrawMode(plane);break;
    case Qt::Key_5:_scene.setDrawMode(points);break;
    case Qt::Key_6:_scene.setDrawMode(chess);break;
    case Qt::Key_7:_scene.setDrawMode(lines);break;

    //OTRAS OPCIONES
    case Qt::Key_0:(_fog)?this->disable_FOG():this->enable_FOG();break;
    case Qt::Key_8:_scene.axis();break;

     //Cambio de camara
     case Qt::Key_9:camera_actual = (this->camera_actual + 1 ) % ncameras;break;

    //Movimiento del personaje
    case Qt::Key_Left: _scene.moverLeft();break;
    case Qt::Key_Right:_scene.moveRight();break;
    case Qt::Key_Up:_scene.moveForward();break;
    case Qt::Key_Down:_scene.moveBackward();break;

    //Acciones del personaje
    case Qt::Key_Z:
        (_scene.getCharacterState()==_normal)?_scene.setCharacterState(_takeHammer):_scene.setCharacterState(_normal);
        break;
    case Qt::Key_X:
        if (_scene.getCharacterState()==_takeHammer) { _scene.setCharacterState(_hitHammer);
        }else _scene.setCharacterState(_normal);
        break;
    case Qt::Key_C:
        _scene.setCharacterState(_screaming);
        break;

    //Cambio de velocidad de la escena
    case Qt::Key_Plus:_scene.speedUp();break;
    case Qt::Key_Minus:_scene.speedDown();break;

    //Cambio de la figura de la galleria
    case Qt::Key_E:_scene.changeElement();break;

     //MOVIMIENTOS DE CAMARA
 //tecla derecha
      case Qt::Key_D:
         /*if ((event->modifiers() & Qt::AltModifier) == Qt::AltModifier) { //si esta pulsada ALT
             cameras[camera_actual].rotateY(-5);
         } if ((event->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier) { //si esta pulsada Cmd
             cameras[camera_actual].rotateZ(-5);
         }else {
             cameras[camera_actual].translateX(2);
         }*/
         cameras[camera_actual].rotateY(-5);
         break;
      //tecla izquierda
      case Qt::Key_A:
         /*if ((event->modifiers() & Qt::AltModifier) == Qt::AltModifier) {
             cameras[camera_actual].rotateY(5);
         } if ((event->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier) {
             cameras[camera_actual].rotateZ(5);
         }else {
             cameras[camera_actual].translateX(-2);
         }*/
        cameras[camera_actual].rotateY(5);
          break;
      //tecla arriba
      case Qt::Key_W:
         /*if ((event->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier) {
              cameras[camera_actual].translateZ(2);
         } if ((event->modifiers() & Qt::AltModifier) == Qt::AltModifier) {
             cameras[camera_actual].rotateX(5);
         }else {
             cameras[camera_actual].translateY(2);
         }*/
        cameras[camera_actual].rotateX(5);
        break;
      //tecla abajo
      case Qt::Key_S:
         /*if ((event->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier) {
              cameras[camera_actual].translateZ(-2);
         } if ((event->modifiers() & Qt::AltModifier) ==Qt::AltModifier) {
             cameras[camera_actual].rotateX(-5);
         }else {
             cameras[camera_actual].translateY(-2);
         }*/
        cameras[camera_actual].rotateX(-5);
        break;

    case Qt::Key_V:
        camera_actual = 4;
             cout << "Introduzca el VRP:" << endl;
             cin >> VRP.x;
             cin >> VRP.y;
             cin >> VRP.z;
             cout << "Introduzca el VPN:" << endl;
             cin >> VPN.x;
             cin >> VPN.y;
             cin >> VPN.z;
             cout << "Introduzca el VUP:" << endl;
             cin >> VUP.x;
             cin >> VUP.y;
             cin >> VUP.z;
             cameras[4].set(VRP,VPN,VUP);
             cout << "Camara activa" << endl;
            break;
    // Primitivas Gráficas
    case Qt::Key_Q: QCoreApplication::exit(0);
    default: QGLWidget::keyPressEvent(event);break;
 }    
 updateGL();
}

void VisorOpenGL::dibujarEscena() {
      this->_scene.draw();
}
