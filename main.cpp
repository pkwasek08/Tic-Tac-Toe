#include "mainwindow.h"
#include "start.h"
#include <QApplication>
#include "rules.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    rules r;
     r.w[0].Plansza();
     r.w[0].show();
   /* MainWindow m;
    m.Plansza();
    m.show();
*/
return a.exec();
}
