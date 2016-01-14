#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T15:14:02
#
#-------------------------------------------------

QT       += core gui
QT       += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PCBAsemblyHelper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pcbviewscene.cpp \
    pcbview.cpp \
    bomentry.cpp \
    bom.cpp \
    markeritem.cpp \
    bomlistwidget.cpp \
    boardlayer.cpp

HEADERS  += mainwindow.h \
    pcbviewscene.h \
    pcbview.h \
    bomentry.h \
    bom.h \
    markeritem.h \
    bomlistwidget.h \
    boardlayer.h

FORMS    += mainwindow.ui
