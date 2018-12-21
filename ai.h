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
    void choosebutton(QPushButton **buttons,const int kol,const int wr,QString znak);
    //Game g;
    int tmp{},w_r{},k_r{};
    int random(int nMin, int nMax);
};

#endif // AI_H
