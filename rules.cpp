#include "rules.h"
#include "mainwindow.h"
#include "start.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QtWidgets>
rules::rules()
{

}

void rules::sprawdz()
{
    MainWindow ma;
    //start s;
    //    for(int i=0;i<wr_r;i++)
    //    {
    //        for(int j=0;j<kol_r;j++)
    //        {

    if(ma.buttons[1][1]->text()=="o" && ma.buttons[2][2]->text()=="o" && ma.buttons[3][3]->text()=="o")
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("WYGRANA");
        msgBox.setText("WYGRAŁEŚ");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        if(msgBox.exec() == QMessageBox::Ok){
            exit(0);
        }
        //            }
        //        }


    }
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
    //srand((unsigned int)time((time_t *)NULL));
    return rand() % (nMax - nMin + 1 ) + nMin;
}
