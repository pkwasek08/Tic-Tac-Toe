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

    wiersze = ui->lineEdit->text();
    kolumny = ui->lineEdit_2->text();
    hide();
    Game g;
    g.Plansza(wiersze,kolumny);
    g.exec();

    if(g.tmp_restart==1)
    {
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        show();
    }
}

void TTTmainWindow::on_buttonBox_rejected()
{
    close();
}
