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
     this->VRP.x=250;this->VRP.y=200;this->VRP.z=0;
     this->VPN.x=1;this->VPN.y=1;this->VPN.z=0;
     this->VUP.x=0;this->VUP.y=1;this->VUP.z=0;
     camera.set(VRP,VPN,VUP);
     cameras.push_back(camera);

     //camara 2
     this->VRP.x=100;this->VRP.y=75;this->VRP.z=200;
     this->VPN.x=1;this->VPN.y=1;this->VPN.z=3;
     this->VUP.x=0;this->VUP.y=1;this->VUP.z=0;
     camera.set(VRP,VPN,VUP);
     camera.fixedCamera(true);
     cameras.push_back(camera);


     //camara 3 vista pajaro
     this->VRP.x=0;this->VRP.y=300;this->VRP.z=0;
     this->VPN.x=0;this->VPN.y=1;this->VPN.z=0;
     this->VUP.x=1;this->VUP.y=0;this->VUP.z=0;
     camera.set(VRP,VPN,VUP);
     cameras.push_back(camera);


     //camara 4 lateral drcho
     this->VRP.x=0;this->VRP.y=40;this->VRP.z=-200;
     this->VPN.x=0;this->VPN.y=0;this->VPN.z=-1;
     this->VUP.x=0;this->VUP.y=1;this->VUP.z=0;
     camera.set(VRP,VPN,VUP);
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
     cameras.push_back(camera);

     //definimos la camara a visualizar
     camera_actual = 0;
     ncameras = 5 ;

     _fog = false;
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
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     //glEnable(GL_NORMALIZE);

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
     //glEnable (GL_FOG);
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
    if ( camera_actual == 4 ) { //this
        _vertex3f position = this->_scene.getCharacterPosition();
        position.y = 100;
        this->VPN.x=0;this->VPN.y=1;this->VPN.z=0;
        this->VUP.x=1;this->VUP.y=0;this->VUP.z=0;
        ((Camera)cameras[camera_actual]).set(position,VPN,VUP);

        aux = ((Camera)cameras[camera_actual]).getVRP();
        cout << "despues " << aux.x << " " << aux.y << " " << aux.z << endl;
    }

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

    //IMPLEMENTAR AQUI LA CAMARA DE SEGUIMIENTO DEL OBJETO PRINCIPAL
    /*
    if(tipo_camara == 1 || tipo_camara == 3){
        switch(tipo_camara){
        case 1: // 1? persona
            vrp = escena.posicionRobot(robotCamara);
            vrp.y = 4;
            break;
        case 3: // 3? persona
            vrp = escena.posicionRobot(robotCamara) + escena.orientacionNegativa(robotCamara)*8;
            vrp.y = 5;
            break;
        }

        vpn = escena.orientacionNegativa(robotCamara);
        vup.x = 0; vup.y = 1; vup.z = 0;

        camara.define(vrp, vpn, vup);
    }


    _vertex3f Escena::posicionRobot(int i){
        return robots[i]->Posicion();
    }

    _vertex3f Escena::orientacionNegativa(int i){
        _vertex3f res;

        res.x = -robots[i]->Orientacion().x;
        res.y = -robots[i]->Orientacion().y;
        res.z = -robots[i]->Orientacion().z;

        return res;
    }
     */

    updateGL();

 }

void VisorOpenGL::keyPressEvent(QKeyEvent *event) {

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
    case Qt::Key_9:
    case Qt::Key_C:
        camera_actual = (this->camera_actual + 1 ) % ncameras;
        break;

    //Movimiento del personaje
    case Qt::Key_Left: _scene.moverLeft();break;
    case Qt::Key_Right:_scene.moveRight();break;
    case Qt::Key_Up:_scene.moveForward();break;
    case Qt::Key_Down:_scene.moveBackward();break;

    //Acciones del personaje
    case Qt::Key_Z:
        (_scene.getCharacterState()==_NORMAL)?_scene.setCharacterState(_TAKE_HAMMER):_scene.setCharacterState(_NORMAL);
        break;
    case Qt::Key_X:
        if (_scene.getCharacterState()==_TAKE_HAMMER) { _scene.setCharacterState(_HIT_HAMMER);
        }else _scene.setCharacterState(_NORMAL);
        break;
    case Qt::Key_V:
        _scene.setCharacterState(_SCREAMING);
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
    /*
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
    */
    // Primitivas Gráficas
    case Qt::Key_Q: QCoreApplication::exit(0);
    default: QGLWidget::keyPressEvent(event);break;
 }    
 updateGL();
}


void VisorOpenGL::dibujarEscena() {
      this->_scene.draw();
}
