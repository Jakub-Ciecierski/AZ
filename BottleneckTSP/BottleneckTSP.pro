#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T00:28:44
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = BottleneckTSP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    oglwidget.cpp \
    bottlenecktsp.cpp \
    Structures/graph.cpp \
    Structures/node.cpp \
    Structures/edge.cpp \
    Structures/forest.cpp

HEADERS  += mainwindow.h \
    oglwidget.h \
    bottlenecktsp.h \
    Structures/graph.h \
    Structures/node.h \
    Structures/edge.h \
    Structures/forest.h

FORMS    += mainwindow.ui
