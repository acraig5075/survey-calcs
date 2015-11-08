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
    calcstab.cpp \
    utils.cpp \
    Dialogs/coordclassdlg.cpp \
    Dialogs/editcoorddlg.cpp \
    coordscontroller.cpp \
    coord.cpp \
    calcscontroller.cpp \
    Dialogs/editjoindlg.cpp \
    Dialogs/selectcoorddlg.cpp \
    Dialogs/doublepolardlg.cpp

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
    calcstab.h \
    utils.h \
    Dialogs/coordclassdlg.h \
    Dialogs/editcoorddlg.h \
    coordscontroller.h \
    coord.h \
    calcscontroller.h \
    Dialogs/editjoindlg.h \
    Dialogs/selectcoorddlg.h \
    Dialogs/doublepolardlg.h

FORMS    += mainwindow.ui \
    stationstab.ui \
    plantab.ui \
    coordstab.ui \
    calcstab.ui \
    Dialogs/coordclassdlg.ui \
    Dialogs/editcoorddlg.ui \
    Dialogs/editjoindlg.ui \
    Dialogs/selectcoorddlg.ui \
    Dialogs/doublepolardlg.ui
