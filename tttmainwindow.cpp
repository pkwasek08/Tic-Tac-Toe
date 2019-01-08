#include "tttmainwindow.h"
#include "ui_tttmainwindow.h"
#include <string>
#include<iostream>
#include<cstdlib>
#include "game.h"


TTTmainWindow::TTTmainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TTTmainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
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

    hide();
    Game g;
    g.Plansza(wiersze,kolumny,znak1,znak2,tryb);
    g.exec();

    if(g.tmp_restart==1)
    {
        ui->spinBox->setValue(10);
        ui->spinBox_2->setValue(10);
        ui->Znak->setCurrentIndex(0);
        ui->Tryb->setCurrentIndex(0);
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
        tryb=0;
        ui->spinBox->setMinimum(3);
        ui->spinBox_2->setMinimum(3);
        ui->spinBox->setValue(3);
        ui->spinBox_2->setValue(3);
    }
    else if(arg1=="1 vs AI")
    {
        tryb=1;
        ui->spinBox->setMinimum(10);
        ui->spinBox_2->setMinimum(10);
    }
}
