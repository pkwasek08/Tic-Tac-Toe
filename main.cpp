#include "mainwindow.h"
#include "start.h"
#include <QApplication>
#include "rules.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.Plansza();
    w.show();

   return a.exec();
}
