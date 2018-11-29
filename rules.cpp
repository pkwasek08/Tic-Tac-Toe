#include "rules.h"
#include "mainwindow.h"
#include "start.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QtWidgets>
rules::rules()
{

}

rules::~rules()
{

}
void rules::wygrana()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("WYGRAŁEŚ");
    msgBox.setText("Jeszcze raz?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Ok);
    if(msgBox.exec() == QMessageBox::No){
        exit(0);
    }
    else
    {
        start s;
        s.setModal(true);
        s.exec();
    }
}
void rules::przegrana()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("PRZEGRAŁEŚ");
    msgBox.setText("Jeszcze raz?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Ok);
    if(msgBox.exec() == QMessageBox::No){
        exit(0);
    }
    else
    {
        start s;
        s.setModal(true);
        s.exec();

    }
}
int rules::random(int nMin, int nMax)
{
    srand((unsigned int)time((time_t *)NULL));
    return rand() % (nMax - nMin + 1 ) + nMin;
}
void rules::sprawdz(QPushButton **buttons,int i,int j,int kol,int wr,QString z)
{
    if(kol<8 && kol<8)
    {
        if(j<kol/2 && i<wr/2)
        {
            if((buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z) ||
                    ( buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z) ||
                    (buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+1]->text()==z))
                if(z=="o") wygrana(); else przegrana();
        }else
        {
            if((buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z) ||
                    ( buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z) ||
                    (buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-1]->text()==z))
                if(z=="o") wygrana(); else przegrana();
        }
    }else
        if(j<kol/2 && i<wr/2)
        {
            if((buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z &&
                buttons[j + i * kol+3]->text()==z && buttons[j + i * kol+4]->text()==z) ||
                    ( buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z &&
                      buttons[j + (i+3) * kol]->text()==z && buttons[j + (i+4) * kol]->text()==z)||
                    (buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+1]->text()==z &&
                     buttons[j + (i+3) * kol+3]->text()==z && buttons[j + (i+4) * kol+4]->text()==z))
                if(z=="o") wygrana(); else przegrana();
        }else
        {
            if((buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z &&
                buttons[j + i * kol-3]->text()==z && buttons[j + i * kol-4]->text()==z) ||
                    ( buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z &&
                      buttons[j + (i-3) * kol]->text()==z && buttons[j + (i-4) * kol]->text()==z)||
                    (buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-1]->text()==z &&
                     buttons[j + (i-3) * kol-3]->text()==z && buttons[j + (i-4) * kol-4]->text()==z))
                if(z=="o") wygrana(); else przegrana();
        }
}


