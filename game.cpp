#include "game.h"
#include "ui_game.h"
#include <QPixmap>
#include <QtWidgets>
#include "resultwindow.h"
#include <cstdlib>
#include <ctime>
#include "ai.h"
#include <QRandomGenerator>
#include <qglobal.h>

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
    //tryb 1 gracz vs gracz, tryb 2 gracz vs AI
    if(tryb_gry==1) tryb=2;
    else tryb=1;

   // wr = wr_ustawione;
   // kol =kol_ustawione;
    gracz1=znak_1gracza;
    gracz2=znak_2gracza;
    wr = 10;
    kol = 10;
    buttons=new QPushButton *[wr*kol];

    for(int i = 0; i < wr*kol; i++) {
        buttons[i] = new QPushButton(this);
        buttons[i]->setText("");
        buttons[i]->setFixedSize(btnSize);
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
                    ai.choosebutton(buttons,kol,wr,gracz2);
                    sprawdz(gracz2);
                }
            }

        }
    }
}

int Game::random(int nMin, int nMax)
{
    //  srand(time(0));
    //qsrand(qrand());
    qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));
    //  return bounded(nMin,nMax);
    return qrand() % (nMax - nMin + 1 ) + nMin;
}
//sprawdza czy ktoś wygrał
void Game::sprawdz(const QString z)
{
    int zab=0;
    for(int i=0;i<wr;i++)
    {
        tmp=0;
        for(int j=0;j<kol;j++)
        {
            if(wr<10 && kol<10)
            { //mniejsza plansza
                if(i<=wr/2)
                {
                    if( buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z) //pion gora
                        if(zab==0)
                        {
                            if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                            zab++;
                        }
                    //skosy górna cześć
                    if(j + (i+2) * kol-2>=(i+2)*kol && j + (i+2) * kol-2<(i+3)*kol) // skos 1 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z)
                            if(zab==0)
                            {
                                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                                zab++;
                            }
                    }
                    if(j + (i+2) * kol+2<(i+3)*kol && j + (i+2) * kol+2>=(i+2)*kol) // skos 2 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z)
                            if(zab==0)
                            {
                                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                                zab++;
                            }
                    }
                }
                else if(i>=wr/2)
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z) //pion dół
                        if(zab==0)
                        {
                            if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                            zab++;
                        }
                    //skosy dolna część
                    if(j + (i-2) * kol-2>=(i-2)*kol && j + (i-2) * kol-2<(i-3)*kol) //skos 1 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z)
                            if(zab==0)
                            {
                                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                                zab++;
                            }
                    }
                    if((j + (i-2) * kol)-2>=(i-2)*kol && (j + (i-2) * kol)-2<(i-3)*kol) //skos 2 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z)
                            if(zab==0)
                            {
                                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                                zab++;
                            }
                    }
                }
                if(j<=kol/2)
                    if(buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z) //poziom lewy
                        if(zab==0)
                        {
                            if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                            zab++;
                        }
                        else if(j>kol/2)
                            if(buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z) //poziom prawy
                                if(zab==0)
                                {
                                    if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                                    zab++;
                                }
            }else //wieksza plansza
            {
                if(i<=wr/2)
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z &&
                            buttons[j + (i+3) * kol]->text()==z && buttons[j + (i+4) * kol]->text()==z) //pion gora
                        if(zab==0)
                        {
                            if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                            zab++;
                        }
                    //skosy górna część
                    if(j + (i+4) * kol-4>=(i+4)*kol && j + (i+4) * kol-4<(i+5)*kol) // skos 1 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z &&
                                buttons[j + (i+3) * kol-3]->text()==z && buttons[j + (i+4) * kol-4]->text()==z)
                            if(zab==0)
                            {
                                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                                zab++;
                            }
                    }
                    if(j + (i+4) * kol+4<(i+5)*kol && j + (i+4) * kol+4>=(i+4)*kol) // skos 2 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z &&
                                buttons[j + (i+3) * kol+3]->text()==z && buttons[j + (i+4) * kol+4]->text()==z)
                            if(zab==0)
                            {
                                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                                zab++;
                            }
                    }
                }
                else if(i>=wr/2)
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z &&
                            buttons[j + (i-3) * kol]->text()==z && buttons[j + (i-4) * kol]->text()==z)//pion dol
                        if(zab==0)
                        {
                            if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                            zab++;
                        }
                    //skosy dolna cześć
                    if(j + (i-4) * kol-4>=(i-4)*kol && j + (i-4) * kol-4<(i-5)*kol) //skos 1 wariant
                    {
                        if((buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z &&
                            buttons[(j + (i-3) * kol)-3]->text()==z && buttons[(j + (i-4) * kol)-4]->text()==z))
                            if(zab==0)
                            {
                                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                                zab++;
                            }
                    }
                    if((j + (i-4) * kol)-4>=(i-4)*kol && (j + (i-4) * kol)-4<(i-5)*kol) //skos 2 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z &&
                                buttons[(j + (i-3) * kol)-3]->text()==z && buttons[(j + (i-4) * kol)-4]->text()==z)
                            if(zab==0)
                            {
                                if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                                zab++;
                            }
                    }
                }
                if(j<=kol/2)
                {
                    if((buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z &&
                        buttons[j + i * kol+3]->text()==z && buttons[j + i * kol+4]->text()==z))//poziom lewy
                        if(zab==0)
                        {
                            if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                            zab++;
                        }
                }
                else if(j>kol/2)
                    if(buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z &&
                            buttons[j + i * kol-3]->text()==z && buttons[j + i * kol-4]->text()==z)//poziom prawy
                        if(zab==0)
                        {
                            if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                            zab++;
                        }
            }
        }
    }
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

