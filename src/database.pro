QT += sql

CONFIG += debug

DESTDIR = bin
TARGET = db

SOURCES += main.cpp \
           mainwindow.cpp \
           database/database.cpp

HEADERS += mainwindow.h \
           database/database.h

FORMS += mainform.ui
