#ifndef RULES_H
#define RULES_H

#include "mainwindow.h"
#include <QMainWindow>
#include <QPixmap>
#include <QtWidgets>

class rules
{
public:
    rules();
    void wygrana();
    void przegrana();
    int random(int nMin, int nMax);
    void sprawdz(QPushButton **tab,int i=0,int j=0,int kol=0,int wr=0,QString z="o");

    ~rules();
};

#endif // RULES_H
