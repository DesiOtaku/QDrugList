#-------------------------------------------------
#
# Project created by QtCreator 2015-12-16T22:51:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QDrugList
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    druginputedit.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    druginputedit.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    database.qrc \
    images.qrc
