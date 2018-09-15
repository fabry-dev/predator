#-------------------------------------------------
#
# Project created by QtCreator 2018-04-04T09:17:34
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = predator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cans.cpp \
    tap.cpp \
    game.cpp \
    email.cpp

HEADERS  += mainwindow.h \
    cans.h \
    tap.h \
    game.h \
    email.h

FORMS    += mainwindow.ui


