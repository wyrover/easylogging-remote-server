#-------------------------------------------------
#
# Project created by QtCreator 2013-09-22T22:15:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = remote-server
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

DEFINES += _ELPP_QT_LOGGING \
     _ELPP_STL_LOGGING \
     _ELPP_LOG_UNORDERED_MAP \
     _ELPP_THREAD_SAFE \
     _ELPP_DEFAULT_LOG_FILE='"\\"logs/server.log\\""' \
     _ELPP_STRICT_SIZE_CHECK \
     SERVER_REQUIRES_PERMISSION \
     SERVER_PASSKEY=123

QMAKE_CC = icpc
QMAKE_CXX = icpc
QMAKE_LINK = icpc

SOURCES += main.cpp \
    credentials.cpp \
    request_type.cpp

HEADERS  += \
    easylogging++.h \
    credentials.h \
    request_type.h

FORMS    +=
