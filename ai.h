#ifndef AI_H
#define AI_H

#include <QPixmap>
#include <QtWidgets>
#include <QApplication>
#include <QWidget>
#include "game.h"


class AI
{
public:
    AI();

    void choosebutton(QPushButton **buttons,const int kol,const int wr,QString gracz,QString znak_ai);
    //Game g;

    int tmp{};
    int random(int nMin, int nMax);
    int markButtons(QPushButton **buttons,const int kol,int i,int j,QString znak);
    int direction(QPushButton **buttons,const int kol,const int wr,QString gracz,QString znak_ai);
    int block(QPushButton **buttons,const int kol,const int wr,QString znak,QString znak_ai);
    int win(QPushButton **buttons,const int kol,const int wr,QString znak);
    void markButtons2(QPushButton **buttons,const int kol,int i,int j,QString znak);
private:
   int w_r{},k_r{};
    int w_ai{},k_ai{};
    int temp_kolumn{},temp_wier{};
    int blokada{};
    int dir=0;

};

#endif // AI_H
