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
     _ELPP_DISABLE_ASSERT \
     _ELPP_PREVENT_FATAL_ABORT \
     SERVER_REQUIRES_PERMISSION \
     SERVER_PASSKEY=123

COMPILER = g++
QMAKE_CC = $$COMPILER
QMAKE_CXX = $$COMPILER
QMAKE_LINK = $$COMPILER

SOURCES += main.cc \
    credentials.cc \
    server.cc \
    json_packet.cc \
    requests/request_type.cc \
    requests/request.cc \
    requests/write_logs_request.cc \
    requests/new_logger_request.cc \
    requests/configuration_update_request.cc \
    requests/request_factory.cc

HEADERS  += \
    easylogging++.h \
    credentials.h \
    server.h \
    json_packet.h \
    requests/request_type.h \
    requests/request.h \
    requests/write_logs_request.h \
    requests/new_logger_request.h \
    requests/configuration_update_request.h \
    requests/request_factory.h

INCLUDEPATH += third_party
LIBS += -L../src/third_party -ljsoncpp

OTHER_FILES += \
    ../conf/log.conf
