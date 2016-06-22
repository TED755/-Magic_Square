#-------------------------------------------------
#
# Project created by QtCreator 2016-03-03T21:32:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Magic_Square
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    magicsquare.cpp \
    functions.cpp \
    magicsquaremodel.cpp \
    magicdelegate.cpp \
    check_square.cpp

HEADERS  += mainwindow.h \
    magicsquare.h \
    magicsquaremodel.h \
    magicdelegate.h

FORMS +=
