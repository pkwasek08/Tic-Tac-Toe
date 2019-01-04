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
    int temp_kolumn{},temp_wier{};
    void choosebutton(QPushButton **buttons,const int kol,const int wr,QString znak);
    //Game g;
    int tmp{},w_r{},k_r{};
    int w_ai{},k_ai{};
    int random(int nMin, int nMax);
    int dir=0;
    int blokada{};
    void markButtons(QPushButton **buttons,const int kol,const int wr,int i,int j,QString znak);
    int direction(QPushButton **buttons,const int kol,const int wr,QString znak);
};

#endif // AI_H
