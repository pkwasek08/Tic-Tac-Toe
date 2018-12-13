#include "start.h"
#include "ui_start.h"
#include <string>
#include<iostream>
#include<cstdlib>
#include "mainwindow.h"
#include "test.h"

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
            show();
        }else {
          exit(0);
        }


    }
    create_game();
    // delete ui;

}

void start::on_start_rejected()
{
    exit(0);
}
void start::create_game()
{

        test test;
        test.exec();

//    MainWindow mainwindow;
//    mainwindow.exec();
   /* MainWindow *m=new MainWindow;

    m->wr = wiersze.split(" ")[0].toInt(); //zamienia string na int
    m->kol =kolunmy.split(" ")[0].toInt();

    m->Plansza();
    m->show();
    if((rest)==1)
    {
        m->buttons[0]->setText("Dupa");
       // setModal(true);
        // exec();
    }
*/
}
void start::wygrana()
{
    QMessageBox msgBox{},msgBox2{};
    msgBox.setWindowTitle("WYGRAŁEŚ");
    msgBox.setText("Jeszcze raz?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    if(msgBox.exec() == QMessageBox::No){
    rest++;
    }
    else
    {
    }
}
void start::przegrana()
{
    QMessageBox msgBox2{};
    msgBox2.setWindowTitle("PRZEGRAŁEŚ");
    msgBox2.setText("Jeszcze raz?");
    msgBox2.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox2.setDefaultButton(QMessageBox::Ok);
    if(msgBox2.exec() == QMessageBox::No){
        exit(0);
    }
    else
    {
       // MainWindow ww;


    }
}
