#-------------------------------------------------
#
# Project created by QtCreator 2015-06-22T18:43:42
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = survey-calcs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calc.cpp \
    calcfactory.cpp \
    stationstab.cpp \
    stationsquerymodel.cpp \
    plantab.cpp \
    calcslistmodel.cpp \
    coordquerymodel.cpp \
    glwidget.cpp \
    coordstab.cpp \
    calcstab.cpp

HEADERS  += mainwindow.h \
    calc.h \
    calcfactory.h \
    stationstab.h \
    stationsquerymodel.h \
    plantab.h \
    coordquerymodel.h \
    calcslistmodel.h \
    glwidget.h \
    coordstab.h \
    calcstab.h

FORMS    += mainwindow.ui \
    stationstab.ui \
    plantab.ui \
    coordstab.ui \
    calcstab.ui
