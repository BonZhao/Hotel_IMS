#-------------------------------------------------
#
# Project created by QtCreator 2015-03-25T23:20:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hotel
TEMPLATE = app


SOURCES += main.cpp\
        hotel.cpp \
    client.cpp \
    room.cpp \
    timethread.cpp \
    resignin.cpp \
    hotelinfo.cpp

HEADERS  += hotel.h \
    client.h \
    room.h \
    timethread.h \
    resignin.h \
    hotelinfo.h

FORMS    += hotel.ui \
    resignin.ui

RESOURCES += \
    image.qrc
