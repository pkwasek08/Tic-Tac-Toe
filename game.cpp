#include "game.h"
#include "ui_game.h"
#include <QPixmap>
#include <QtWidgets>
#include "resultwindow.h"
#include "ai.h"

using namespace std;

AI ai;

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);


}

void Game::Plansza(int wr_ustawione, int kol_ustawione,QString znak_1gracza,QString znak_2gracza,int tryb_gry) //int tryb
{
    //znak_1gracza - znak którym przy grze z AI posługuje się gracz
    //znak_2gracza - znak którym posługuje się AI
    //tryb 1 gracz vs gracz, tryb 2 gracz vs AI
    if(tryb_gry==1) tryb=2;
    else tryb=1;

    wr = wr_ustawione;
    kol =kol_ustawione;
    gracz1=znak_1gracza;
    gracz2=znak_2gracza;

    buttons=new QPushButton *[wr*kol];

    for(int i = 0; i < wr*kol; i++) {
        buttons[i] = new QPushButton(this);
        buttons[i]->setText("");
        buttons[i]->setFixedSize(btnSize);
        buttons[i]->setAutoDefault(0);
    }

    QGridLayout *btnLayout = new QGridLayout(this);
    for(int i = 0; i < wr; i++) {
        for(int j = 0; j < kol; j++) {
            btnLayout->addWidget(buttons[j + i * kol], 0 + i, j);
            btnLayout->setSpacing(0);
            connect(buttons[j + i * kol],SIGNAL(released()),this,SLOT(Klik()));
        }
    }
    this->setLayout(btnLayout);
}
Game::~Game()
{
    delete ui;
    ///for (int i=0; i<wr*kol; i++)
    // {
    delete [] buttons;
    //}
    // delete [] buttons;
    delete view;
}

//pojawienie sie kołka + sprawdzenie
void Game::Klik()
{
    QObject *button = QObject::sender();
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(button == buttons[j + i * kol])
            {
                if(gracz==0 && tryb==1)
                {
                    buttons[j + i * kol]->setText(gracz1);
                    buttons[j + i * kol]->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(245,38,38);}");
                    buttons[j + i * kol]->setDisabled(1);
                    sprawdz(gracz1);
                    gracz++;
                }
                else if(gracz==1 && tryb==1)
                {

                    buttons[j + i * kol]->setText(gracz2);
                    buttons[j + i * kol]->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
                    buttons[j + i * kol]->setDisabled(1);
                    sprawdz(gracz2);
                    gracz--;
                }
                if(tryb==2)
                {
                    buttons[j + i * kol]->setText(gracz1);
                    buttons[j + i * kol]->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(245,38,38);}");
                    buttons[j + i * kol]->setDisabled(1);
                    sprawdz(gracz1);
                    //  AI::choosebutton(buttons,kol,wr,gracz2);
                    // ai.direction(buttons,kol,wr,gracz2)
                    ai.choosebutton(buttons,kol,wr,gracz1,gracz2);
                    sprawdz(gracz2);
                }
            }

        }
    }
}
//sprawdza czy ktoś wygrał
int Game::sprawdz(const QString z)
{
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(i+4<wr && buttons[j + (i) * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i+3) * kol]->text()==z &&  buttons[j + (i+4) * kol]->text()==z)
            {
                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                return 1;
            }
            if(i-4>=0 && buttons[j + (i) * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + (i-3) * kol]->text()==z && buttons[j + (i-4) * kol]->text()==z)
            {
                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                return 1;
            }
            if(j+4<kol && buttons[j + (i) * kol]->text()==z && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol+2]->text()==z && buttons[j + (i) * kol+3]->text()==z && buttons[j + (i) * kol+4]->text()==z)
            {
                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                return 1;
            }
            if(j-4>=0 && buttons[j + (i) * kol]->text()==z && buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol-2]->text()==z && buttons[j + (i) * kol-3]->text()==z && buttons[j + (i) * kol-4]->text()==z)
            {
                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                return 1;
            }
            if(j+4<kol && i+4<wr && buttons[j + (i) * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + (i+3) * kol+3]->text()==z && buttons[j + (i+4) * kol+4]->text()==z)
            {
                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                return 1;
            }
            if(j-4>=0 && i-4>=0 && buttons[j + (i) * kol]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i-3) * kol-3]->text()==z && buttons[j + (i-4) * kol-4]->text()==z)
            {
                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                return 1;
            }
            if(j-4>=0 && i+4<wr && buttons[j + (i) * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i+3) * kol-3]->text()==z && buttons[j + (i+4) * kol-4]->text()==z)
            {
                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                return 1;
            }
            if(j+4<kol && i-4>=0 && buttons[j + (i) * kol]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + (i-3) * kol+3]->text()==z && buttons[j + (i-4) * kol+4]->text()==z)
            {
                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                return 1;
            }
        }
    }
    return 0;
}

void Game::koniec(QString z)
{
    ResultWindow res;
    res.wybor(z);
    if(res.wynik==1)
    {
        tmp_restart=1;
        ai.tmp=0;

        close();
    }
    else {
        tmp_restart=0;
        close();
    }
}

