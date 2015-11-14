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
    calcfactory.cpp \
    stationstab.cpp \
    plantab.cpp \
    glwidget.cpp \
    coordstab.cpp \
    calcstab.cpp \
    utils.cpp \
    Dialogs/coordclassdlg.cpp \
    Dialogs/editcoorddlg.cpp \
    coordscontroller.cpp \
    calcscontroller.cpp \
    Dialogs/editjoindlg.cpp \
    Dialogs/doublepolardlg.cpp \
    Dialogs/selectcoorddlg.cpp \
    Models/observationsquerymodel.cpp \
    Types/observation.cpp \
    Models/calcslistmodel.cpp \
    Models/coordquerymodel.cpp \
    Models/stationsquerymodel.cpp \
    Types/calc.cpp \
    Types/coord.cpp \
    Types/occupied.cpp \
    Types/joins.cpp \
    Types/polars.cpp \
    Types/dpolars.cpp

HEADERS  += mainwindow.h \
    calcfactory.h \
    stationstab.h \
    plantab.h \
    glwidget.h \
    coordstab.h \
    calcstab.h \
    utils.h \
    Dialogs/coordclassdlg.h \
    Dialogs/editcoorddlg.h \
    coordscontroller.h \
    calcscontroller.h \
    Dialogs/editjoindlg.h \
    Dialogs/selectcoorddlg.h \
    Dialogs/doublepolardlg.h \
    Models/observationsquerymodel.h \
    Types/observation.h \
    Models/calcslistmodel.h \
    Models/coordquerymodel.h \
    Models/stationsquerymodel.h \
    Types/calc.h \
    Types/coord.h \
    Types/occupied.h \
    Types/joins.h \
    Types/polars.h \
    Types/dpolars.h \
    calctypes.h

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

DISTFILES +=

RESOURCES += \
    Resources/icons.qrc
