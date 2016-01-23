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
    map.cpp \
    pathplanner.cpp \
    gridpathplanner.cpp \
    polygonpathplanner.cpp \
    dijkstrapathplanner.cpp \
    astarpathplanner.cpp

HEADERS  += pathplanningdemonstrator.h \
    map.h \
    config.h \
    pathplanner.h \
    gridpathplanner.h \
    polygonpathplanner.h \
    dijkstrapathplanner.h \
    astarpathplanner.h

FORMS    += pathplanningdemonstrator.ui
