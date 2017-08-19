#-------------------------------------------------
#
# Project created by QtCreator 2017-08-15T09:17:04
#
#-------------------------------------------------

QT       += core gui
QT       += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FilmDBase_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    databasemanager.cpp \
    addtotabledialog.cpp

HEADERS  += mainwindow.h \
    databasemanager.h \
    addtotabledialog.h

FORMS    += mainwindow.ui \
    addtotabledialog.ui
