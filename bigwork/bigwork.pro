#-------------------------------------------------
#
# Project created by QtCreator 2019-05-18T11:36:53
#
#-------------------------------------------------

QT       += core gui
QT       += winextras
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bigwork
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    basicadt.cpp
HEADERS  += mainwindow.h \
    basicadt.h
FORMS    += mainwindow.ui

RESOURCES += \
    images/image.qrc \
    translator.qrc

TRANSLATIONS =$$PWD/translator/Lidar_en.ts \
        $$PWD/translator/Lidar_zh.ts

RC_ICONS=btn.ico
