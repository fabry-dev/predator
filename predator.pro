#-------------------------------------------------
#
# Project created by QtCreator 2018-04-04T09:17:34
#
#-------------------------------------------------

QT       += core gui quick
CONFIG += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = predator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cans.cpp \
    tap.cpp \
    game.cpp \
    email.cpp \
    keyboard.cpp

HEADERS  += mainwindow.h \
    cans.h \
    tap.h \
    game.h \
    email.h \
    keyboard.h

FORMS    += mainwindow.ui


LIBS += -lquickmail

