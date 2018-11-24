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
}
void MainWindow::Plansza()
{
    rules r;
    start s;
    s.setModal(true);
    s.exec();
    wr = s.wiersze.split(" ")[0].toInt(); //zamienia string na int
    kol = s.kolunmy.split(" ")[0].toInt();
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            this->buttons[i][j]=new QPushButton();
            this->buttons[i][j]->setMinimumWidth(60);
            this->buttons[i][j]->setMinimumHeight(60);
            view->addWidget(this->buttons[i][j],i,j);
            connect(this->buttons[i][j],SIGNAL(released()),this,SLOT(Klik()));
        }
    }
    ui->centralWidget->setLayout(view);
    setCentralWidget(ui->centralWidget);

    //1 ruch komputera
    if(wr/2>3 && kol/2>3)
    {
        srand((unsigned int)time((time_t *)NULL));
        w_r=rand()%(wr-6)+3;
        k_r=rand()%(kol-6)+3;
    }else
    {
        srand((unsigned int)time((time_t *)NULL));
        w_r=rand()%wr;
        k_r=rand()%kol;
    }
    buttons[w_r][k_r]->setText("x");
    buttons[w_r][k_r]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    buttons[w_r][k_r]->setDisabled(1);
    max_w=w_r;
    max_k=k_r;
}
MainWindow::~MainWindow()
{
    delete ui;
    free(buttons);
    delete button;
    for (unsigned i = 30; i > 0; --i)
        delete[] *buttons[i]; //usuwa matrix tablice
    //delete[][] *buttons;
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
                AI();
            }
            if(kol<8 && kol<8)
            {
                if(j<kol/2 && i<wr/2)
                {
                    if((buttons[i][j]->text()=="o" && buttons[i][j+1]->text()=="o" && buttons[i][j+2]->text()=="o") ||
                            ( buttons[i][j]->text()=="o" && buttons[i+1][j]->text()=="o" && buttons[i+2][j]->text()=="o") ||
                            (buttons[i][j]->text()=="o" && buttons[i+1][j+1]->text()=="o" && buttons[i+2][j+2]->text()=="o"))
                        r.wygrana();
                }else
                {
                    if((buttons[i][j]->text()=="o" && buttons[i][j-1]->text()=="o" && buttons[i][j-2]->text()=="o") ||
                            ( buttons[i][j]->text()=="o" && buttons[i-1][j]->text()=="o" && buttons[i-2][j]->text()=="o") ||
                            (buttons[i][j]->text()=="o" && buttons[i-1][j-1]->text()=="o" && buttons[i-2][j-2]->text()=="o"))
                        r.wygrana();
                }
            }else
                if(j<kol/2 && i<wr/2)
                {
                    if((buttons[i][j]->text()=="o" && buttons[i][j+1]->text()=="o" && buttons[i][j+2]->text()=="o" &&
                            buttons[i][j+3]->text()=="o" && buttons[i][j+4]->text()=="o") ||
                            ( buttons[i][j]->text()=="o" && buttons[i+1][j]->text()=="o" && buttons[i+2][j]->text()=="o" &&
                              buttons[i+3][j]->text()=="o" && buttons[i+4][j]->text()=="o")||
                            (buttons[i][j]->text()=="o" && buttons[i+1][j+1]->text()=="o" && buttons[i+2][j+2]->text()=="o" &&
                             buttons[i+3][j+3]->text()=="o" && buttons[i+4][j+4]->text()=="o"))
                        r.wygrana();
                }else
                { if((buttons[i][j]->text()=="o" && buttons[i][j-1]->text()=="o" && buttons[i][j-2]->text()=="o" &&
                      buttons[i][j-3]->text()=="o" && buttons[i][j-4]->text()=="o") ||
                      ( buttons[i][j]->text()=="o" && buttons[i-1][j]->text()=="o" && buttons[i-2][j]->text()=="o" &&
                        buttons[i-3][j]->text()=="o" && buttons[i-4][j]->text()=="o")||
                      (buttons[i][j]->text()=="o" && buttons[i-1][j-1]->text()=="o" && buttons[i-2][j-2]->text()=="o" &&
                       buttons[i-3][j-3]->text()=="o" && buttons[i-4][j-4]->text()=="o"))
                        r.wygrana();
                }
        }
    }
}

void MainWindow::AI()
{
    rules r;
    int w_ai{},k_ai{};

    do
    {
        if(w_r==0 || k_r==0) {w_r=1; k_r=1;}
        if(w_r==max_w || k_r==max_k) {w_r=max_w-1; k_r=max_k-1;}
        w_ai=r.random(w_r-1,w_r+1);
        k_ai=r.random(k_r-1,k_r+1);
    }
    while(w_ai<0 || k_ai<0 || w_ai>max_w || k_ai>max_k ||
          buttons[w_ai][k_ai]->text()=="o" || buttons[w_ai][k_ai]->text()=="x");

   // Sleep(1000);
    buttons[w_ai][k_ai]->setText("x");
    buttons[w_ai][k_ai]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    buttons[w_ai][k_ai]->setDisabled(1);

    w_r=w_ai;
    k_r=k_ai;

    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(kol<8 && kol<8)
            {
                if(j<kol/2 && i<wr/2)
                {
                    if((buttons[i][j]->text()=="x" && buttons[i][j+1]->text()=="x" && buttons[i][j+2]->text()=="x") ||
                            ( buttons[i][j]->text()=="x" && buttons[i+1][j]->text()=="x" && buttons[i+2][j]->text()=="x") ||
                            (buttons[i][j]->text()=="x" && buttons[i+1][j+1]->text()=="x" && buttons[i+2][j+2]->text()=="x"))
                        r.przegrana();
                }else
                {
                    if((buttons[i][j]->text()=="x" && buttons[i][j-1]->text()=="x" && buttons[i][j-2]->text()=="x") ||
                            ( buttons[i][j]->text()=="x" && buttons[i-1][j]->text()=="x" && buttons[i-2][j]->text()=="x") ||
                            (buttons[i][j]->text()=="x" && buttons[i-1][j-1]->text()=="x" && buttons[i-2][j-2]->text()=="x"))
                        r.przegrana();
                }
            }else
                if(j<kol/2 && i<wr/2)
                {
                    if((buttons[i][j]->text()=="x" && buttons[i][j+1]->text()=="x" && buttons[i][j+2]->text()=="x" &&
                            buttons[i][j+3]->text()=="x" && buttons[i][j+4]->text()=="x") ||
                            ( buttons[i][j]->text()=="x" && buttons[i+1][j]->text()=="x" && buttons[i+2][j]->text()=="x" &&
                              buttons[i+3][j]->text()=="x" && buttons[i+4][j]->text()=="x")||
                            (buttons[i][j]->text()=="x" && buttons[i+1][j+1]->text()=="x" && buttons[i+2][j+2]->text()=="x" &&
                             buttons[i+3][j+3]->text()=="x" && buttons[i+4][j+4]->text()=="x"))
                        r.przegrana();
                }else
                { if((buttons[i][j]->text()=="x" && buttons[i][j-1]->text()=="x" && buttons[i][j-2]->text()=="x" &&
                      buttons[i][j-3]->text()=="x" && buttons[i][j-4]->text()=="x") ||
                      ( buttons[i][j]->text()=="x" && buttons[i-1][j]->text()=="x" && buttons[i-2][j]->text()=="x" &&
                        buttons[i-3][j]->text()=="x" && buttons[i-4][j]->text()=="x")||
                      (buttons[i][j]->text()=="x" && buttons[i-1][j-1]->text()=="x" && buttons[i-2][j-2]->text()=="x" &&
                       buttons[i-3][j-3]->text()=="x" && buttons[i-4][j-4]->text()=="x"))
                        r.przegrana();
                }
        }
    }


}
