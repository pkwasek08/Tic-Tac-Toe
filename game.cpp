#include "game.h"
#include "ui_game.h"
#include <QPixmap>
#include <QtWidgets>
#include "resultwindow.h"
using namespace std;

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

}

void Game::Plansza(QString wr_ustawione, QString kol_ustawione)
{
    wr = wr_ustawione.split(" ")[0].toInt(); //zamienia string na int
    kol =kol_ustawione.split(" ")[0].toInt();
    //wr = 10;
    //kol = 10;
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

    // 1 ruch komputera
    if(wr/2>3 && kol/2>3)
    {
        w_r=random(3,wr-4);
        k_r=random(3,kol-4);
    }else
    {
        w_r=random(0,wr-1);
        k_r=random(0,kol-1);
    }
    buttons[k_r + w_r * kol]->setText("x");
    buttons[k_r + w_r * kol]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    buttons[k_r + w_r * kol]->setDisabled(1);
    max_w=w_r;
    max_k=k_r;
}
Game::~Game()
{
    delete ui;
    for (int i=0; i<wr*kol; i++)
    {
        delete [] buttons;
    }
    // delete [] buttons;
    //close();
}

//pojawienie sie kołka + sprawdzenie
void Game::Klik()
{
    //rules r;
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
                sprawdz("o");
            }
        }
    }
}

void Game::AI()
{

}
int Game::random(int nMin, int nMax)
{
    srand((unsigned int)time((time_t *)NULL));
    return rand() % (nMax - nMin + 1 ) + nMin;
}
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
                            if(z=="o") koniec("o"); else koniec("x");
                            zab++;
                        }
                    //skosy górna cześć
                    if(j + (i+2) * kol-2>=(i+2)*kol && j + (i+2) * kol-2<(i+3)*kol) // skos 1 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z)
                            if(zab==0)
                            {
                                if(z=="o") koniec("o"); else koniec("x");
                                zab++;
                            }
                    }
                    if(j + (i+2) * kol+2<(i+3)*kol && j + (i+2) * kol+2>=(i+2)*kol) // skos 2 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z)
                            if(zab==0)
                            {
                                if(z=="o") koniec("o"); else koniec("x");
                                zab++;
                            }
                    }
                }
                else if(i>=wr/2)
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z) //pion dół
                        if(zab==0)
                        {
                            if(z=="o") koniec("o"); else koniec("x");
                            zab++;
                        }
                    //skosy dolna część
                    if(j + (i-2) * kol-2>=(i-2)*kol && j + (i-2) * kol-2<(i-3)*kol) //skos 1 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z)
                            if(zab==0)
                            {
                                if(z=="o") koniec("o"); else koniec("x");
                                zab++;
                            }
                    }
                    if((j + (i-2) * kol)-2>=(i-2)*kol && (j + (i-2) * kol)-2<(i-3)*kol) //skos 2 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z)
                            if(zab==0)
                            {
                                if(z=="o") koniec("o"); else koniec("x");
                                zab++;
                            }
                    }
                }
                if(j<=kol/2)
                    if(buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z) //poziom lewy
                        if(zab==0)
                        {
                            if(z=="o") koniec("o"); else koniec("x");
                            zab++;
                        }
                        else if(j>kol/2)
                            if(buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z) //poziom prawy
                                if(zab==0)
                                {
                                    if(z=="o") koniec("o"); else koniec("x");
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
                            if(z=="o") koniec("o"); else koniec("x");
                            zab++;
                        }
                    //skosy górna część
                    if(j + (i+4) * kol-4>=(i+4)*kol && j + (i+4) * kol-4<(i+5)*kol) // skos 1 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z &&
                                buttons[j + (i+3) * kol-3]->text()==z && buttons[j + (i+4) * kol-4]->text()==z)
                            if(zab==0)
                            {
                                if(z=="o") koniec("o"); else koniec("x");
                                zab++;
                            }
                    }
                    if(j + (i+4) * kol+4<(i+5)*kol && j + (i+4) * kol+4>=(i+4)*kol) // skos 2 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z &&
                                buttons[j + (i+3) * kol+3]->text()==z && buttons[j + (i+4) * kol+4]->text()==z)
                            if(zab==0)
                            {
                                if(z=="o") koniec("o"); else koniec("x");
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
                            if(z=="o") koniec("o"); else koniec("x");
                            zab++;
                        }
                    //skosy dolna cześć
                    if(j + (i-4) * kol-4>=(i-4)*kol && j + (i-4) * kol-4<(i-5)*kol) //skos 1 wariant
                    {
                        if((buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z &&
                            buttons[(j + (i-3) * kol)-3]->text()==z && buttons[(j + (i-4) * kol)-4]->text()==z))
                            if(zab==0)
                            {
                                if(z=="o") koniec("o"); else koniec("x");
                                zab++;
                            }
                    }
                    if((j + (i-4) * kol)-4>=(i-4)*kol && (j + (i-4) * kol)-4<(i-5)*kol) //skos 2 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z &&
                                buttons[(j + (i-3) * kol)-3]->text()==z && buttons[(j + (i-4) * kol)-4]->text()==z)
                            if(zab==0)
                            {
                                if(z=="o") koniec("o"); else koniec("x");
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
                            if(z=="o") koniec("o"); else koniec("x");
                            zab++;
                        }
                }
                else if(j>kol/2)
                    if(buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z &&
                            buttons[j + i * kol-3]->text()==z && buttons[j + i * kol-4]->text()==z)//poziom prawy
                        if(zab==0)
                        {
                            if(z=="o") koniec("o"); else koniec("x");
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
        close();
    }
    else {
        tmp_restart=0;
        close();
    }
}
