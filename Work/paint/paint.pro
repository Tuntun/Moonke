#-------------------------------------------------
#
# Project created by QtCreator 2014-06-08T18:52:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = paint
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    painter.cpp

HEADERS  += mainwindow.h \
    painter.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    image.qrc
