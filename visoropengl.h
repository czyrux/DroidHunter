#ifndef VISOROPENGL
#define VISOROPENGL

#include <QGLWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QTimer>

#include "scene.h"
#include "matrix.h"
#include "camera.h"

 class VisorOpenGL: public QGLWidget {
     Q_OBJECT

 public:
     VisorOpenGL(QWidget *parent = 0);
     ~VisorOpenGL();

     QSize minimumSizeHint() const;
     QSize sizeHint() const;

 public slots:
     void idle();

 signals:
     void quit();

 protected:
    void initializeGL();
    void disable_FOG();
    void enable_FOG();
    void paintGL();
    void resizeGL(int width, int height);

    void keyPressEvent(QKeyEvent *event);

    void setCamara();
    void setProjection();
    void dibujarEscena();

 private:
    QPoint lastPos;

    Scene _scene;
    GLint Draw_type;

    _vertex3f VPN;
    _vertex3f VUP;
    _vertex3f VRP;

    vector<Camera> cameras;
    int camera_actual;
    int ncameras;
    bool _fog;

    QTimer *timer;

    int Window_width;
    int Window_height;
    int Front_plane;
    int Back_plane;

    void normalizeAngle(float angle);
 };

#endif

