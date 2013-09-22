#-------------------------------------------------
#
# Project created by QtCreator 2013-09-22T22:15:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = remote-server
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

DEFINES += _ELPP_QT_LOGGING \
     _ELPP_STL_LOGGING \
     _ELPP_LOG_UNORDERED_MAP \
     _ELPP_THREAD_SAFE \
     SERVER_REQUIRES_PERMISSION \
     SERVER_PASSKEY=123

QMAKE_CC = g++
QMAKE_CXX = g++
QMAKE_LINK = g++

SOURCES += main.cpp \
    credentials.cpp \
    request_type.cpp

HEADERS  += \
    easylogging++.h \
    credentials.h \
    request_type.h

FORMS    +=
