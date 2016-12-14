#-------------------------------------------------
#
# Project created by QtCreator 2016-12-13T23:46:26
#
#-------------------------------------------------

QT       -= gui
QT       += network serialport

TARGET = DataPort
TEMPLATE = lib

DEFINES += DATAPORT_LIBRARY

SOURCES += dataport.cpp \
    serialdataport.cpp \
    networkdataport.cpp

HEADERS += dataport.h\
        dataport_global.h \
    serialdataport.h \
    networkdataport.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
