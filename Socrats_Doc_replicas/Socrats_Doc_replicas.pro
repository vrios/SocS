#-------------------------------------------------
#
# Project created by QtCreator 2013-10-28T23:48:25
#
#-------------------------------------------------
win32 {
QMAKE_LFLAGS += -static-libgcc
}

QT       += core

QT       -= gui


TARGET = Socrats_Doc_replicas
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++11
TEMPLATE = app


SOURCES += main.cpp \
    ../Socrats_Doc_Gui__codigo_base/world-funcao_update.cpp \
    ../Socrats_Doc_Gui__codigo_base/world.cpp \
    ../Socrats_Doc_Gui__codigo_base/memory.cpp \
    ../Socrats_Doc_Gui__codigo_base/dbscan.cpp \
    ../Socrats_Doc_Gui__codigo_base/agents.cpp

HEADERS += \
    ../Socrats_Doc_Gui__codigo_base/world.h \
    ../Socrats_Doc_Gui__codigo_base/agents.h
