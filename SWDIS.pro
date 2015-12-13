#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T15:04:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SWDIS
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    adjacencymatrix.cpp \
    route.cpp \
    ialgorithm.cpp \
    antscolony.cpp

HEADERS  += dialog.h \
    adjacencymatrix.h \
    route.h \
    ialgorithm.h \
    antscolony.h

FORMS    += dialog.ui
