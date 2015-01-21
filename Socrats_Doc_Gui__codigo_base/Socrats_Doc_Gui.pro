#-------------------------------------------------
#
# Project created by QtCreator 2012-10-30T16:22:48
#
#-------------------------------------------------

QT       += core gui

TARGET = Socrats_Doc_Gui
QMAKE_CXXFLAGS += -std=c++11
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    agents.cpp \
    world.cpp \
    world-funcao_update.cpp \
    dbscan.cpp \
    memory.cpp\
space.cpp\


HEADERS  += mainwindow.h \
    agents.h \
    world.h\
space.h

INCLUDEPATH += C:\Users\Vrios\C++ bibliotecas\boost_1_51_0

FORMS    += mainwindow.ui
QT += widgets
