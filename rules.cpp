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
        for(int j=0;j<kol;j++)
        {
            if(kol<10 && kol<10)
            {
                if(i<wr/2)
                {
                    if(( buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z) //pion
                            || (buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z) //skos 1 kierunek
                            || (buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z)) //skos 2 kierunek
                        if(z=="o") wygrana(); else przegrana();
                }
                else if(i>=wr/2)
                {
                    if((buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z) //pion
                            || (buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z) //ukos1
                            || (buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z)) //ukos2
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
                    if(( buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z &&
                         buttons[j + (i+3) * kol]->text()==z && buttons[j + (i+4) * kol]->text()==z)|| //pion
                            (buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z &&
                             buttons[j + (i+3) * kol+3]->text()==z && buttons[j + (i+4) * kol+4]->text()==z) || //skos 1 kierunek
                            (buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z &&
                             buttons[j + (i+3) * kol-3]->text()==z && buttons[j + (i+4) * kol-4]->text()==z)) //skos 2 kierunek
                        if(z=="o") wygrana(); else przegrana();
                }
                else if(i>=wr/2)
                {
                    if((buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z &&
                        buttons[j + (i-3) * kol]->text()==z && buttons[j + (i-4) * kol]->text()==z) || //pion
                            (buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z &&
                             buttons[j + (i-3) * kol-3]->text()==z && buttons[j + (i-4) * kol-4]->text()==z) || //ukos 1 kierunek
                            (buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z &&
                             buttons[j + (i-3) * kol+3]->text()==z && buttons[j + (i-4) * kol+4]->text()==z)) //ukos 2 kierunek
                        if(z=="o") wygrana(); else przegrana();
                }
                if(j<=kol/2)
                    if((buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z &&
                        buttons[j + i * kol+3]->text()==z && buttons[j + i * kol+4]->text()==z)) //poziom +
                        if(z=="o") wygrana(); else przegrana();
                    else if(j>kol/2)
                        if((buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z &&
                            buttons[j + i * kol-3]->text()==z && buttons[j + i * kol-4]->text()==z)) //poziom -
                            if(z=="o") wygrana(); else przegrana();
            }
        }
    }
}


