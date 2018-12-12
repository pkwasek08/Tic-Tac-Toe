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

    }
}
int rules::random(int nMin, int nMax)
{
    srand((unsigned int)time((time_t *)NULL));
    return rand() % (nMax - nMin + 1 ) + nMin;
}
void rules::sprawdz(QPushButton **buttons,const int kol,const int wr,const QString z)
{
    for(int i=0;i<wr;i++)
    {
        tmp=0;
        for(int j=0;j<kol;j++)
        {
            if(wr<10 && kol<10)
            {
                if(i<wr/2)
                {
                    if( buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z) //pion
                        if(z=="o") wygrana(); else przegrana();
                }
                else if(i>=wr/2)
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z) //pion
                        if(z=="o") wygrana(); else przegrana();
                }
                if(j<=kol/2)
                    if(buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z) //poziom +
                        if(z=="o") wygrana(); else przegrana();
                    else if(j>kol/2)
                        if(buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z) //poziom -
                            if(z=="o") wygrana(); else przegrana();
            }else
            {
                if(i<wr/2)
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z &&
                            buttons[j + (i+3) * kol]->text()==z && buttons[j + (i+4) * kol]->text()==z) //pion gora
                        if(z=="o") wygrana(); else przegrana();
                }
                else if(i>=wr/2)
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z &&
                            buttons[j + (i-3) * kol]->text()==z && buttons[j + (i-4) * kol]->text()==z)//pion dol
                        if(z=="o") wygrana(); else przegrana();
                }
                if(j<=kol/2)
                    if((buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z &&
                        buttons[j + i * kol+3]->text()==z && buttons[j + i * kol+4]->text()==z))//poziom lewy
                        if(z=="o") wygrana(); else przegrana();
                    else if(j>kol/2)
                        if(buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z &&
                                buttons[j + i * kol-3]->text()==z && buttons[j + i * kol-4]->text()==z)//poziom prawy
                            if(z=="o") wygrana(); else przegrana();
            }
        }
    }
        for(int i=(wr-1);i>0;i--)
        {
            for(int j=tmp;j<kol;j++)
            {
                if(wr>=10 && kol>=10)
                {
                if((buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z &&
                    buttons[j + (i-3) * kol-3]->text()==z && buttons[j + (i-4) * kol-4]->text()==z) || //skos 1 kierunek
                        (buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z &&
                         buttons[j + (i-3) * kol+3]->text()==z && buttons[j + (i-4) * kol+4]->text()==z)) //skos 2 kierunek))
                    if(z=="o") wygrana(); else przegrana();
                }else
                {
                    if((buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z) //skos 1 kierunek
                        || (buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z))
                    if(z=="o") wygrana(); else przegrana();//skos 2 kierunek)
                }
            }
            tmp++;
        }
        tmp = kol;
        for(int i=0;i<wr;i++)
        {
            for(int j=0;j<tmp;j++)
            {
                if(wr>=10 && kol>=10)
                {
                if((buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z &&
                    buttons[j + (i+3) * kol+3]->text()==z && buttons[j + (i+4) * kol+4]->text()==z) || //skos 1 kierunek
                        (buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z &&
                         buttons[j + (i+3) * kol-3]->text()==z && buttons[j + (i+4) * kol-4]->text()==z))
                    if(z=="o") wygrana(); else przegrana(); //skos 2 kierunek
                }else
                {
                    if((buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z) //skos1 maly
                    || (buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z)) //skos2 maly
                        if(z=="o") wygrana(); else przegrana(); //skos 2 kierunek
                }
            }
            tmp--;
        }
}


