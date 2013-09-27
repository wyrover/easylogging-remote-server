#-------------------------------------------------
#
# Project created by QtCreator 2013-09-22T22:15:20
#
#-------------------------------------------------

QT       += core network

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

COMPILER = g++
QMAKE_CC = $$COMPILER
QMAKE_CXX = $$COMPILER
QMAKE_LINK = $$COMPILER

SOURCES += main.cc \
    credentials.cc \
    request_type.cc \
    write_logs_request.cc \
    server.cc \
    request.cc \
    json_packet.cc

HEADERS  += \
    easylogging++.h \
    credentials.h \
    request_type.h \
    request.h \
    write_logs_request.h \
    server.h \
    json_packet.h

INCLUDEPATH += third_party
LIBS += -L../src/third_party -ljsoncpp

OTHER_FILES += \
    ../conf/log.conf
