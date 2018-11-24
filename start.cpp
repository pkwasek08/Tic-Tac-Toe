#include "start.h"
#include "ui_start.h"
#include "mainwindow.h"
#include <string>
#include<iostream>
#include<cstdlib>

start::start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
}

start::~start()
{
    delete ui;
}

void start::on_buttonBox_accepted()
{

    wiersze = ui->lineEdit->text();
    kolunmy = ui->lineEdit_2->text();

    //zabezpiecznie przed podaniem zlej liczby
    if(wiersze.split(" ")[0].toInt()<=0 || kolunmy.split(" ")[0].toInt()<=0)
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Błąd");
        msgBox.setText("Podaj liczbę większą od 0");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        //msgBox.QMessageBox::Warning;
        if(msgBox.exec() == QMessageBox::Ok){
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            MainWindow w;
            w.Plansza();
        }else {
          exit(0);
        }

    }
    // delete ui;

}

void start::on_start_rejected()
{
    exit(0);
}
