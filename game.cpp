#include "game.h"
using namespace std;

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
}

void Game::Plansza(int wr_ustawione, int kol_ustawione,QString znak_1gracza,QString znak_2gracza,int tryb_gry,int wiel_przyciskow,bool cofnij,QString zaczyna) //int tryb
{
    //znak_1gracza - znak którym przy grze z AI posługuje się gracz
    //znak_2gracza - znak którym posługuje się AI
    //tryb 1 gracz vs gracz, tryb 2 gracz vs AI
    //back true = przycisk cofania aktywny

    if(tryb_gry==1) tryb=2;
    else tryb=1;
    back=cofnij;
    wr = wr_ustawione;
    kol =kol_ustawione;
    gracz1=znak_1gracza;
    gracz2=znak_2gracza;

    if(tryb==1 && zaczyna=="x")
    {
        gracz1="x";
        gracz2="o";
    }
    else if(tryb==1 && zaczyna=="o") {
        gracz1="o";
        gracz2="x";
    }

    if(tryb==2 && zaczyna=="x" && znak_1gracza=="o")
    {
        trybik=3;
    }else if(tryb==2 && zaczyna=="o" && znak_1gracza=="x")
    {
        trybik=3;
    }

    if(gracz1=="x")
        paint1 = QStringLiteral("QPushButton{font-size: %1px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}").arg(wiel_przyciskow);
    else {
        paint1 = QStringLiteral("QPushButton{font-size: %1px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(245,38,38);}").arg(wiel_przyciskow);
    }
    if(gracz2=="x")
        paint2 = QStringLiteral("QPushButton{font-size: %1px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}").arg(wiel_przyciskow);
    else {
        paint2 = QStringLiteral("QPushButton{font-size: %1px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(245,38,38);}").arg(wiel_przyciskow);
    }

    ai.setColor(paint2);
    //ustawia wielkosc przyciskow
    const QSize buttonSize = QSize(wiel_przyciskow, wiel_przyciskow);

    buttons=new QPushButton *[wr*kol];

    for(int i = 0; i < wr*kol; i++) {
        buttons[i] = new QPushButton(this);
        buttons[i]->setText("");
        buttons[i]->setFixedSize(buttonSize);
        buttons[i]->setAutoDefault(0);
    }


    // "box"+static_cast<QString>(dbmanager->findUserBox(name)+48);
    buttonsLayout = new QGridLayout(this);

    if(cofnij==true)
    {
        ai.cofnij_proby=2;
        bb = new QPushButton(this);
        buttonsLayout->setMenuBar(bb);
        if(tryb==2)
            bb->setText("Cofnij (2 próby)");
        else bb->setText("Cofnij");
        bb->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(192,192,192);}");
        bb->setFixedSize(maximumWidth(),40);
        bb->setDisabled(1);
        connect(bb,SIGNAL(released()),this,SLOT(Cofnij()));
    }

    for(int i = 0; i < wr; i++) {
        for(int j = 0; j < kol; j++) {
            buttonsLayout->addWidget(buttons[j + i * kol], 0 + i, j);
            buttonsLayout->setSpacing(0);
            buttons[j + i * kol]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(220,220,220);}");

            connect(buttons[j + i * kol],SIGNAL(released()),this,SLOT(Klik()));
        }
    }
    this->setLayout(buttonsLayout);
    if(trybik==3)
        ai.choosebutton(buttons,kol,wr,gracz1,gracz2);
}
Game::~Game()
{
    delete ui;
    delete [] buttons;
    delete buttonsLayout;
    delete bb;
    delete view;
}

//pojawienie sie kołka + sprawdzenie
void Game::Klik()
{
    QObject *button = QObject::sender();
    // xd->setDisabled(0);
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(button == buttons[j + i * kol])
            {
                if(gracz==0 && tryb==1)
                {
                    cofnij_w_gracz=i;
                    cofnij_k_gracz=j;
                    buttons[j + i * kol]->setText(gracz1);
                    buttons[j + i * kol]->setStyleSheet(paint1);
                    buttons[j + i * kol]->setDisabled(1);
                    sprawdz(gracz1);
                    gracz++;
                    if(back==true)
                        if(cofnij1==0)
                        {
                            bb->setText("Cofnij");
                            bb->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(192,192,192);}");
                            bb->setDisabled(0);
                        }
                        else {
                            bb->setText("Powodzenia");
                            bb->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(0,0,0);}");
                            bb->setDisabled(1);
                        }

                }
                else if(gracz==1 && tryb==1)
                {
                    cofnij_w_gracz=i;
                    cofnij_k_gracz=j;
                    buttons[j + i * kol]->setText(gracz2);
                    buttons[j + i * kol]->setStyleSheet(paint2);
                    buttons[j + i * kol]->setDisabled(1);
                    sprawdz(gracz2);
                    gracz--;
                    if(back==true)
                        if(cofnij2==0)
                        {
                            bb->setText("Cofnij");
                            bb->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(192,192,192);}");
                            bb->setDisabled(0);
                        }
                        else {
                            bb->setText("Powodzenia");
                            bb->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(0,0,0);}");
                            bb->setDisabled(1);
                        }
                }
                if(tryb==2)
                {
                    cofnij_w_gracz=i;
                    cofnij_k_gracz=j;
                    buttons[j + i * kol]->setText(gracz1);
                    buttons[j + i * kol]->setStyleSheet(paint1);
                    buttons[j + i * kol]->setDisabled(1);
                    sprawdz(gracz1);
                    ai.choosebutton(buttons,kol,wr,gracz1,gracz2);
                    sprawdz(gracz2);
                    if(back==true)
                    {
                        if(ai.cofnij_proby>0)
                        {
                            bb->setDisabled(0);
                            bb->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(192,192,192);}");
                        }
                    }
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
            if(wr<10 && j<10)
            {
                if(i+2<wr && buttons[j + (i) * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z)
                {
                    if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                    return 1;
                }
                if(i-2>=0 && buttons[j + (i) * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z)
                {
                    if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                    return 1;
                }
                if(j+2<kol && buttons[j + (i) * kol]->text()==z && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol+2]->text()==z)
                {
                    if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                    return 1;
                }
                if(j-2>=0 && buttons[j + (i) * kol]->text()==z && buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol-2]->text()==z)
                {
                    if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                    return 1;
                }
                if(j+2<kol && i+2<wr && buttons[j + (i) * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z)
                {
                    if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                    return 1;
                }
                if(j-2>=0 && i-2>=0 && buttons[j + (i) * kol]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z)
                {
                    if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                    return 1;
                }
                if(j-2>=0 && i+2<wr && buttons[j + (i) * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z)
                {
                    if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                    return 1;
                }
                if(j+2<kol && i-2>=0 && buttons[j + (i) * kol]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z)
                {
                    if(z==gracz1) koniec(gracz1); else koniec(gracz2);
                    return 1;
                }
            } else
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
    }
    if(ai.test(buttons,kol,wr)==1)
    {
        koniec("REMIS");
        return 0;
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

void Game::Cofnij()
{
    QObject *button = QObject::sender();
    if(button==bb)
    {
        if(tryb==1 && gracz==1)
        {
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setDisabled(0);
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setText("");
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(220,220,220);}");
            bb->setText("Powodzenia");
            bb->setStyleSheet(paint_cofnij_black);
            bb->setDisabled(1);
            gracz=0;
            cofnij1++;
        }
        else if(tryb==1 && gracz==0)
        {
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setDisabled(0);
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setText("");
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(220,220,220);}");
            bb->setText("Powodzenia");
            bb->setStyleSheet(paint_cofnij_black);
            bb->setDisabled(1);
            gracz=1;
            cofnij2++;
        }
        else if(tryb==2 && ai.cofnij_proby==2)
        {
            if(ai.tmp==1)
                tmp=0;
            if(ai.tmp==2)
                tmp=1;
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setDisabled(0);
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setText("");
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(220,220,220);}");
            buttons[ai.cofnij_w_ai*kol+ai.cofnij_k_ai]->setDisabled(0);
            buttons[ai.cofnij_w_ai*kol+ai.cofnij_k_ai]->setText("");
            buttons[ai.cofnij_w_ai*kol+ai.cofnij_k_ai]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(220,220,220);}");
            bb->setText("Cofnij (1 próba)");
            ai.cofnij_proby--;
            bb->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(96,96,96);}");
            bb->setDisabled(1);
        }
        else if(tryb==2 && ai.cofnij_proby==1)
        {
            if(ai.tmp==1)
                tmp=0;
            if(ai.tmp==2)
                tmp=1;
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setDisabled(0);
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setText("");
            buttons[cofnij_w_gracz*kol+cofnij_k_gracz]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(220,220,220);}");
            buttons[ai.cofnij_w_ai*kol+ai.cofnij_k_ai]->setDisabled(0);
            buttons[ai.cofnij_w_ai*kol+ai.cofnij_k_ai]->setText("");
            buttons[ai.cofnij_w_ai*kol+ai.cofnij_k_ai]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(220,220,220);}");
            bb->setText("Powodzenia");
            bb->setStyleSheet(paint_cofnij_black);
            bb->setDisabled(1);
            ai.cofnij_proby--;
        }
    }
}
