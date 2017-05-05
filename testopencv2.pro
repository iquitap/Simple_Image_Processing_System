#-------------------------------------------------
#
# Project created by QtCreator 2016-07-20T12:42:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testopencv
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH+=g:\opencv\opencv\build\include\opencv \
  g:\opencv\opencv\build\include\opencv2 \
                   g:\opencv\opencv\build\include
LIBS+=G:\opencv\opencv\build\x64\vc12\lib\opencv_world310.lib
LIBS+=G:\opencv\opencv\build\x64\vc12\lib\opencv_world310d.lib
