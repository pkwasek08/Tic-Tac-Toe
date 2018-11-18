#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "start.h"
#include <QPixmap>
#include <QtWidgets>
#include "game.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "rules.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rules r;
    start s;
    s.setModal(true);
    s.exec();
    wr = s.wiersze.split(" ")[0].toInt();
    kol = s.kolunmy.split(" ")[0].toInt();
    r.wr_r=wr;
    r.kol_r=kol;
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            buttons[i][j]=new QPushButton();
            buttons[i][j]->setMinimumWidth(60);
            buttons[i][j]->setMinimumHeight(60);
            view->addWidget(buttons[i][j],i,j);
            connect(buttons[i][j],SIGNAL(released()),this,SLOT(Klik()));
        }
    }

    ui->centralWidget->setLayout(view);
    setCentralWidget(ui->centralWidget);

    //1 ruch komputera

    srand(time(NULL));
    w_r=rand()%wr;
    k_r=rand()%kol;

    buttons[w_r][k_r]->setText("x");
    buttons[w_r][k_r]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    buttons[w_r][k_r]->setDisabled(1);


}
void MainWindow::Plansza()
{

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Klik()
{
    rules r;
    QObject* button = QObject::sender();
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(button == buttons[i][j])
            {
                buttons[i][j]->setText("o");
                buttons[i][j]->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(245,38,38);}");
                buttons[i][j]->setDisabled(1);
            }

        }
    }
}
