#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TTTmainWindow t;
    t.show();

    return a.exec();
}
