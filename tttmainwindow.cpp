#include "tttmainwindow.h"
#include "ui_tttmainwindow.h"
#include <string>
#include<iostream>
#include<cstdlib>
#include "game.h"
#include <QDesktopWidget>


TTTmainWindow::TTTmainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TTTmainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    QDesktopWidget dw;
    x=dw.width();
    y=dw.height()-160;
    max_wr=y/30;
    max_kol=x/30;
    ui->spinBox_2->setMaximum(max_kol);
    ui->spinBox->setMaximum(max_wr);


}

TTTmainWindow::~TTTmainWindow()
{
    delete ui;
}

void TTTmainWindow::on_Zakoncz_clicked()
{
    close();
}

void TTTmainWindow::on_Start_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);

}

void TTTmainWindow::on_buttonBox_accepted()
{
    wiersze = ui->spinBox->text().split(" ")[0].toInt();
    kolumny = ui->spinBox_2->text().split(" ")[0].toInt();
    wiel_przyciskow=y/wiersze;
    hide();
    Game g;
    //Game g(0,Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    g.Plansza(wiersze,kolumny,znak1,znak2,tryb,wiel_przyciskow,cofnij,zaczyna);
    g.exec();



    if(g.tmp_restart==1)
    {
        /* ui->spinBox->setValue(wiersze);
        ui->spinBox_2->setValue(kolumny);
        ui->Znak->setCurrentIndex(0);
        ui->Tryb->setCurrentIndex(tryb);*/
        show();
    }
}

void TTTmainWindow::on_buttonBox_rejected()
{
    close();
}

void TTTmainWindow::on_Znak_activated(const QString &arg1)
{
    if(arg1=="kółko")
    {
        znak1="o";
        znak2="x";
    }
    else
    {
        znak1="x";
        znak2="o";
    }
}

void TTTmainWindow::on_Tryb_activated(const QString &arg1)
{
    if(arg1=="1 vs 1")
    {
        ui->comboBox_2->setDisabled(1);
        tryb=0;
        ui->spinBox->setMinimum(3);
        ui->spinBox_2->setMinimum(3);
        ui->spinBox->setValue(3);
        ui->spinBox_2->setValue(3);
    }
    else if(arg1=="1 vs AI")
    {
        ui->comboBox_2->setDisabled(0);
        tryb=1;
        ui->spinBox->setMinimum(10);
        ui->spinBox_2->setMinimum(10);
    }
}


void TTTmainWindow::on_comboBox_activated(const QString &arg1)
{
    if(arg1=="Tak")
        cofnij=true;
    else {
        cofnij=false;
    }
}

void TTTmainWindow::on_comboBox_2_activated(const QString &arg1)
{
    if(arg1=="krzyżyk")
        zaczyna="x";
    else zaczyna="o";
}
