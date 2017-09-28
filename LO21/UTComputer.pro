#-------------------------------------------------
#
# Project created by QtCreator 2016-06-05T12:25:27
#
#-------------------------------------------------

QT       += core gui multimedia
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UTComputer
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        Atome.cpp \
        Complexe.cpp \
        Controleur.cpp \
        Entiere.cpp \
        Expression.cpp \
        Litterale.cpp \
        Pile.cpp \
        Programme.cpp \
        Rationelle.cpp \
        Reelle.cpp \
    LitteraleManager.cpp \
    computermanager.cpp \
    Contexte.cpp

HEADERS  += mainwindow.h \
    Atome.hpp \
    Complexe.h \
    Controleur.hpp \
    Entiere.h \
    Expression.hpp \
    Litterale.hpp \
    Numerique.h \
    Pile.hpp \
    Programme.hpp \
    Rationelle.h \
    Reelle.h \
    ComputerException.h \
    LitteraleManager.h \
    ComputerManager.h \
    Contexte.hpp

FORMS    += mainwindow.ui
