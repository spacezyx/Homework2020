# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = lab3

QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle

HEADERS = \
   $$PWD/termio.h \
   haniotower.h \
   mystack.h

SOURCES = \
   $$PWD/hanoi.cpp \
   haniotower.cpp

INCLUDEPATH = \
    $$PWD/.

#DEFINES =

