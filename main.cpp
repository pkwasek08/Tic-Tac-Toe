#include "mainwindow.h"
#include "start.h"
#include "game.h"
#include <QApplication>
#include "rules.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.Plansza();
    w.show();


//    rules r;
//    r.sprawdz();
//    w.show();



   return a.exec();
}