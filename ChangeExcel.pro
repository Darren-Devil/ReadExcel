#-------------------------------------------------
#
# Project created by QtCreator 2018-08-22T14:16:29
#
#-------------------------------------------------

QT       += core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChangeExcel
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    ExcelBase.cpp \
    qvariantlistlistmodel.cpp \
    tableview.cpp

HEADERS  += mainwindow.h \
    ExcelBase.h \
    qvariantlistlistmodel.h \
    tableview.h

FORMS    += mainwindow.ui
