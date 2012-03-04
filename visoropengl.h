/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file visoropengl.h
 * @brief Implementation of parameters 3D from OpenGL
 * @author Antonio Gutierrez Martinez
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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

