#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "start.h"
#include <QPixmap>
#include <QtWidgets>
#include "rules.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
void MainWindow::Plansza()
{
    rules r;
   // start s;
    //s.setModal(true);
    //s.exec();
    //wr = s.wiersze.split(" ")[0].toInt(); //zamienia string na int
    //kol = s.kolunmy.split(" ")[0].toInt();

    wr = 10;
    kol = 10;
    buttons=new QPushButton *[wr*kol];

    for(int i = 0; i < wr*kol; i++) {
        buttons[i] = new QPushButton(ui->centralWidget);
        buttons[i]->setText("( ͡° ͜ʖ ͡°)");
        buttons[i]->setFixedSize(btnSize);
    }

    QGridLayout *btnLayout = new QGridLayout(ui->centralWidget);
    for(int i = 0; i < wr; i++) {
        for(int j = 0; j < kol; j++) {
            btnLayout->addWidget(buttons[j + i * kol], 0 + i, j);
            btnLayout->setSpacing(0);
            connect(buttons[j + i * kol],SIGNAL(released()),this,SLOT(Klik()));
        }
    }
    ui->centralWidget->setLayout(btnLayout);

    // 1 ruch komputera
    if(wr/2>3 && kol/2>3)
    {
        w_r=r.random(3,wr-4);
        k_r=r.random(3,kol-4);
    }else
    {
        w_r=r.random(0,wr-1);
        k_r=r.random(0,kol-1);
    }
    buttons[k_r + w_r * kol]->setText("x");
    buttons[k_r + w_r * kol]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    buttons[k_r + w_r * kol]->setDisabled(1);
    max_w=w_r;
    max_k=k_r;
}
MainWindow::~MainWindow()
{
    delete ui;
   for (int i=0; i<wr; i++)
       {
          delete [] buttons[i];
       }
    delete [] buttons;
   //close();
}

//pojawienie sie kołka + sprawdzenie
void MainWindow::Klik()
{
    rules r;
    QObject *button = QObject::sender();
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(button == buttons[j + i * kol])
            {
                buttons[j + i * kol]->setText("o");
                buttons[j + i * kol]->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(245,38,38);}");
                buttons[j + i * kol]->setDisabled(1);
                r.sprawdz(buttons,kol,wr,"o");
               /* MainWindow *w = new MainWindow;
                 w->Plansza();
                 w->show();*/
            }
        }
    }
}

void MainWindow::AI()
{

}
