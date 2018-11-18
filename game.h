#ifndef GAME_H
#define GAME_H

//#include "mainwindow.h"
#include "start.h"
#include <QDialog>


class game
{
    //Q_OBJECT
public:

    game(int wr,int kol);
    int rand_wr(int wr);
    int rand_kol(int kol);
   // void sprawdz();
    void AI();
};

#endif // GAME_H
