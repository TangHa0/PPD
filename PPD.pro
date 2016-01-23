#-------------------------------------------------
#
# Project created by QtCreator 2016-01-23T12:55:55
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PPD
TEMPLATE = app


SOURCES += main.cpp\
        pathplanningdemonstrator.cpp \
    obstacle.cpp \
    map.cpp \
    vertex.cpp \
    pathplanner.cpp \
    gridpathplanner.cpp \
    polygonpathplanner.cpp \
    dijkstrapathplanner.cpp

HEADERS  += pathplanningdemonstrator.h \
    obstacle.h \
    map.h \
    vertex.h \
    config.h \
    pathplanner.h \
    gridpathplanner.h \
    polygonpathplanner.h \
    dijkstrapathplanner.h

FORMS    += pathplanningdemonstrator.ui
