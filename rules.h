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
    //MainWindow *w_new;
    void wygrana();
    void przegrana();
    int random(int nMin, int nMax);
    void sprawdz(QPushButton **tab,const int kol=0,const int wr=0,const QString z="o");
    int tmp; //i=0,j=0;

    ~rules();
};

#endif // RULES_H
