# configuration Qt
QT       += core gui opengl widgets
TEMPLATE  = app

# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
	LIBS     += -lGL -lGLU
}

# nom de l'exe genere
TARGET 	  = Casse briques

# fichiers sources/headers
SOURCES	+= main.cpp myglwidget.cpp \
    ball.cpp \
    brick.cpp \
    game.cpp \
    platform.cpp \
    wall.cpp \
    camera.cpp \
    mainwindow.cpp \
    losedialog.cpp \
    scores.cpp \
    rank.cpp \
    rankdialog.cpp
HEADERS += myglwidget.h \
    ball.h \
    brick.h \
    game.h \
    platform.h \
    wall.h \
    camera.h \
    mainwindow.h \
    losedialog.h \
    scores.h \
    rank.h \
    rankdialog.h
CONFIG+=c++11

FORMS += \
    mainwindow.ui \
    losedialog.ui \
    rankdialog.ui \
    camera.ui \
    camera.ui

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_features2d2413 \
    -lopencv_calib3d2413

QT += concurrent
