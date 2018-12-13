#ifndef RULES_H
#define RULES_H

#include "mainwindow.h"
#include <QMainWindow>
#include <QPixmap>
#include <QtWidgets>
#include "start.h"

class rules
{
public:

    void restart(QWidget *parent);
    rules();

    MainWindow *w = new MainWindow[2];
    int chose=0;

    start *s = new start;
    int tralala;
    int random(int nMin, int nMax);
    void sprawdz(QPushButton **tab,const int kol=0,const int wr=0,const QString z="o" );
    int tmp; //i=0,j=0;

    ~rules();
};

#endif // RULES_H
