#-------------------------------------------------
#
# Project created by QtCreator 2017-04-03T21:55:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = handGesture
TEMPLATE = app


SOURCES += main.cpp\
        handgesture.cpp \
    common.cpp \
    database_api.cpp

HEADERS  += handgesture.h \
    common.h \
    database_api.h

FORMS    += handgesture.ui

LIBS    += -L /usr/local/lib/ \
        -lopencv_core -lopencv_features2d \
        -lopencv_highgui -lopencv_imgproc \
        -lopencv_ml -lopencv_video -lopencv_contrib \
        -lopencv_objdetect

LIBS    += -L /usr/local/lib/ \
        -lsqlite3

QMAKE_CXXFLAGS += -std=c++11 -O2 -w -static -lsqlite3
