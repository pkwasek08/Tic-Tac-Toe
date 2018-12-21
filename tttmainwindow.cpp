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
    wiersze = ui->lineEdit->text().split(" ")[0].toInt();
    kolumny = ui->lineEdit_2->text().split(" ")[0].toInt();
    if(wiersze<3 || wiersze >=20 || kolumny<3 || kolumny >=20)
    {
        show();
        QMessageBox msgBox;
        msgBox.setWindowTitle("Błąd");
        msgBox.setText("Podaj liczbę większą od 0 i mniejszą od 25");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        if(msgBox.exec() == QMessageBox::Ok){
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
           // ui->Znak->setCurrentIndex(0);
        }
    }else
    {
        hide();
        Game g;
        g.Plansza(wiersze,kolumny,znak1,znak2,tryb);
        g.exec();

        if(g.tmp_restart==1)
        {
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->Znak->setCurrentIndex(0);
            ui->Tryb->setCurrentIndex(0);
            show();
        }
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
        tryb=0;
    else if(arg1=="1 vs AI")
        tryb=1;
}
