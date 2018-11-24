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
    void sprawdz();
    void wygrana();
    void przegrana();
    int random(int nMin, int nMax);

    ~rules();
};

#endif // RULES_H
