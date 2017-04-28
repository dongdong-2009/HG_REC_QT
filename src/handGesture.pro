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
    drawdialog.cpp

HEADERS  += handgesture.h \
    common.h \
    drawdialog.h

FORMS    += handgesture.ui \
    drawdialog.ui

LIBS    += -L /usr/local/lib/ \
        -lopencv_core -lopencv_features2d \
        -lopencv_highgui -lopencv_imgproc \
        -lopencv_ml -lopencv_video -lopencv_contrib \
        -lopencv_objdetect

QMAKE_CXXFLAGS += -std=c++11 -O2 -w -static

RESOURCES += \
    resource.qrc
