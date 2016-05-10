#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T00:28:44
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BottleneckTSP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    oglwidget.cpp

HEADERS  += mainwindow.h \
    oglwidget.h

FORMS    += mainwindow.ui
