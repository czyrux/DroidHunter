#-------------------------------------------------
#
# Project created by QtCreator 2012-03-04T20:37:43
#
#-------------------------------------------------

QT       += core gui
QT += opengl
INCLUDEPATH += .

TARGET = DroidHunter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    wasp.cpp \
    visoropengl.cpp \
    starship.cpp \
    scene.cpp \
    particle.cpp \
    objects.cpp \
    map.cpp \
    file_ply_stl.cpp \
    droid.cpp \
    circle.cpp \
    character.cpp \
    car.cpp \
    camera.cpp \
    ball_monster.cpp \
    axis.cpp \
    tree3D.cpp \
    egg.cpp \
    plants.cpp \
    window.cpp \
    droidHead.cpp \
    droidhand.cpp

HEADERS  += mainwindow.h \
    wasp.h \
    visoropengl.h \
    vertex.h \
    starship.h \
    scene.h \
    random.h \
    particle.h \
    objects.h \
    matrix.h \
    materials.h \
    map.h \
    hierarchyObject.h \
    file_ply_stl.h \
    droid.h \
    circle.h \
    character.h \
    car.h \
    camera.h \
    ball_monster.h \
    axis.h \
    tree3D.h \
    egg.h \
    plants.h \
    window.h \
    droidHead.h \
    droidhand.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    resources/stars.jpg \
    resources/stars.gif \
    resources/snail.ply \
    resources/lizard.ply \
    resources/land.jpg \
    resources/iroko.jpg \
    resources/grava.jpg \
    resources/grass.ply \
    resources/floor.jpg \
    resources/earth2.jpg \
    resources/earth.jpg \
    resources/Chicken.ply \
    resources/cesped.jpg \
    resources/carretera.jpg \
    resources/big_porsche.ply \
    resources/beethoven.ply \
    resources/ant.ply
