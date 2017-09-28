#include "Expression.hpp"
#include "Controleur.hpp"
#include "Pile.hpp"
#include "Entiere.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include "ComputerManager.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
