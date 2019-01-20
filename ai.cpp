#include "ai.h"
#include <QTime>
#include <qglobal.h>
#include <time.h>

AI::AI()
{
    //font_rozmiar=font;
    QTime time = QTime::currentTime();
    qsrand(static_cast<uint>(time.msec()));
    w_ai=0;
    k_ai=0;
    tmp=0;
}

void AI::choosebutton(QPushButton **buttons,const int kol,const int wr,QString gracz,QString znak_ai)
{
    // 1 ruch komputera
    if(tmp==0)
    {
        do
        {
            w_r=random(3,wr-4);
            k_r=random(3,kol-4);
        }
        while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x");
        markButtons(buttons,kol,w_r,k_r,znak_ai);
        w_ai=w_r;
        k_ai=k_r;
        tmp++;
    }else if(tmp==1) //2 ruch
    {
        do
        {
            QTime time = QTime::currentTime();
            qsrand(static_cast<uint>(time.msec()));
            w_r=random(w_ai-1,w_ai+1);
            k_r=random(k_ai-1,k_ai+1);
        }
        while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x");
        markButtons(buttons,kol,w_r,k_r,znak_ai);
        tmp++;
    }
    else
    {
        if(test(buttons,kol,wr)==0)
        {
            if(win(buttons,kol,wr,znak_ai,znak_ai)==0)
            {
                if(win(buttons,kol,wr,gracz,znak_ai)==0) //metoda win do zablokowania wygranej przeciwnika
                {
                    if(block(buttons,kol,wr,znak_ai,znak_ai)==0) //wykorzystanie metody blokujacej do ataku
                    {
                        if(specialCase(buttons,kol,wr,znak_ai,znak_ai)==0) //atak
                        {
                            if(specialCase(buttons,kol,wr,gracz,znak_ai)==0) //obrona
                            {
                                if(block(buttons,kol,wr,gracz,znak_ai)==0)
                                {
                                    if(direction_2(buttons,kol,wr,gracz,znak_ai)==0)
                                    {
                                        do
                                        {
                                            w_r=random(0,wr-1);
                                            k_r=random(0,kol-1);
                                        }
                                        while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x");
                                        markButtons(buttons,kol,w_r,k_r,znak_ai);
                                        qDebug()<<"Losuje";
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int AI::random(int nMin, int nMax)  //losuje
{
    return qrand() % (nMax - nMin + 1 ) + nMin;
}
int AI::test(QPushButton **buttons, const int kol, const int wr)
{
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(buttons[j + (i) * kol]->text()=="")
                return 0;
        }
    }
    return 1;
}

//wybiera najlepszy kierunek dla ai
int AI::direction_2(QPushButton **buttons,const int kol,const int wr,QString gracz,QString z)
{
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(i-2>=0 && i+2<wr && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + (i+1) * kol]->text()=="" && buttons[j + (i+2) * kol]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
            if(i+2<wr && i-2>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i-1) * kol]->text()=="" && buttons[j + (i-2) * kol]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
            if(j+2<kol && j-2>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol+2]->text()==z && buttons[j + (i) * kol-1]->text()=="" && buttons[j + (i) * kol-2]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
            if(j+2<kol && j-2>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol-2]->text()==z && buttons[j + (i) * kol+1]->text()=="" && buttons[j + (i) * kol+2]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
            if(j-2>=0 && i-2>=0 && i+2<wr && j+2<kol && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i+1) * kol+1]->text()=="" && buttons[j + (i+2) * kol+2]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
            if(j-2>=0 && i-2>=0 && i+2<wr && j+2<kol && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + (i-1) * kol-1]->text()=="" && buttons[j + (i-2) * kol-2]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
            if(j-2>=0 && i-2>=0 && i+2<wr && j+2<kol && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + (i+1) * kol-1]->text()=="" && buttons[j + (i+2) * kol-2]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
            if(j-2>=0 && i-2>=0 && i+2<wr && j+2<kol && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i-1) * kol+1]->text()=="" && buttons[j + (i-2) * kol+2]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
            if(i+2<wr && i-2>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()=="" && buttons[j + (i-2) * kol]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
            if(j+2<kol && j-2>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol+2]->text()=="" && buttons[j + (i) * kol-2]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
            if(j-2>=0 && i-2>=0 && j+1<kol && i+1<wr && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i-2) * kol-2]->text()=="" && buttons[j + (i+2) * kol+2]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
            if(j-2>=0 && i-2>=0 && j+1<kol && i+1<wr && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i-2) * kol+2]->text()=="" && buttons[j + (i+2) * kol-2]->text()=="")
            {
                markButtons(buttons,kol,i,j, z);
                return 1;
            }
        }
    }
    for(int i=2;i<wr-2;i++)
    {
        for(int j=2;j<kol-2;j++)
        {
            if(buttons[j + (i) * kol]->text()==z && (buttons[i*kol+j-1]->text()=="" || buttons[i*kol+j+1]->text()=="" || buttons[(i-1)*kol+j]->text()=="" ||
                    buttons[(i+1)*kol+j]->text()=="" || buttons[(i-1)*kol+j-1]->text()=="" || buttons[(i+1)*kol+j+1]->text()=="" || buttons[(i-1)*kol+j+1]->text()=="" || buttons[(i+1)*kol+j-1]->text()=="") && ((buttons[i*kol+j-1]->text()==z && buttons[i*kol+j+1]->text()==z) || (buttons[(i-1)*kol+j]->text()==z &&
                                                      buttons[(i+1)*kol+j]->text()==z) || (buttons[(i-1)*kol+j-1]->text()==z && buttons[(i+1)*kol+j+1]->text()==z) || (buttons[(i-1)*kol+j+1]->text()==z && buttons[(i+1)*kol+j-1]->text()==z)))
            {
                do
                {
                    QTime time = QTime::currentTime();
                    qsrand(static_cast<uint>(time.msec()));

                    w_r=random(i-1,i+1);
                    k_r=random(j-1,j+1);
                }
                while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x");
                markButtons(buttons,kol,w_r,k_r, z);
                qDebug()<<"Losuje direction";
                return 1;
            }
            else if(buttons[j + (i) * kol]->text()==z && buttons[i*kol+j-1]->text()=="" && (buttons[i*kol+j+1]->text()=="" || buttons[(i-1)*kol+j]->text()=="" ||
                      buttons[(i+1)*kol+j]->text()=="" || buttons[(i-1)*kol+j-1]->text()=="" || buttons[(i+1)*kol+j+1]->text()=="" || buttons[(i-1)*kol+j+1]->text()=="" || buttons[(i+1)*kol+j-1]->text()==""))
            {
                do
                {
                    QTime time = QTime::currentTime();
                    qsrand(static_cast<uint>(time.msec()));

                    w_r=random(i-1,i+1);
                    k_r=random(j-1,j+1);
                }
                while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x");
                markButtons(buttons,kol,w_r,k_r, z);
                qDebug()<<"Losuje direction ostatnie";
                return 1;
            }
        }
    }
    return 0;
}

int AI::markButtons(QPushButton **buttons,const int kol,int i,int j,QString znak)
{
    if(buttons[(i)*kol+j]->text()=="")
    {
        cofnij_w_ai=i;
        cofnij_k_ai=j;
        Sleep(250);
        buttons[(i)*kol+j]->setText(znak);
        buttons[(i)*kol+j]->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
        buttons[(i)*kol+j]->setDisabled(1);
        return 1;
    }
    return 0;
}



int AI::block(QPushButton **buttons, const int kol, const int wr, QString z ,QString znak_ai)
{
    //z- znak gracza
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(i+3<wr && i-1>=0 && buttons[j + (i-1) * kol]->text()=="" && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i+3) * kol]->text()==z)
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(i-3>=0 && i+1<wr && buttons[j + (i+1) * kol]->text()=="" && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + (i-3) * kol]->text()==z)
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && j-1>=0 && buttons[j + (i) * kol+1]->text()=="" && buttons[j + (i) * kol]->text()=="" && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol+2]->text()==z && buttons[j + (i) * kol+3]->text()==z)
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-3>=0 && j+1<kol && buttons[j + (i) * kol+1]->text()=="" && buttons[j + (i) * kol]->text()=="" && buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol-2]->text()==z && buttons[j + (i) * kol-3]->text()==z)
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && i+3<wr && i-1>=0 && j-1>=0 && buttons[j + (i-1) * kol-1]->text()=="" && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + (i+3) * kol+3]->text()==z)
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-3>=0 && i-3>=0 && i+1<wr && j+1<kol && buttons[j + (i+1) * kol+1]->text()=="" && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i-3) * kol-3]->text()==z)
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-3>=0 && i+3<wr && j+1<kol && i-1>=0 && buttons[j + (i-1) * kol+1]->text()=="" && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i+3) * kol-3]->text()==z)
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && i-3>=0 && i+1<wr && j-1>=0 && buttons[j + (i+1) * kol-1]->text()=="" && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + (i-3) * kol+3]->text()==z)
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
        }
    }
    return 0;
}

int AI::win(QPushButton **buttons, const int kol, const int wr, QString z,QString z_ai)
{
    //z - znak ai
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(i+4<wr && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i+3) * kol]->text()==z &&  buttons[j + (i+4) * kol]->text()==z)
            {
                markButtons(buttons,kol,i,j, z_ai);
                return 1;
            }
            if(i-4>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + (i-3) * kol]->text()==z && buttons[j + (i-4) * kol]->text()==z)
            {
                markButtons(buttons,kol,i,j, z_ai);
                return 1;
            }
            if(j+4<kol && buttons[j + (i) * kol]->text()=="" && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol+2]->text()==z && buttons[j + (i) * kol+3]->text()==z && buttons[j + (i) * kol+4]->text()==z)
            {
                markButtons(buttons,kol,i,j, z_ai);
                return 1;
            }
            if(j-4>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol-2]->text()==z && buttons[j + (i) * kol-3]->text()==z && buttons[j + (i) * kol-4]->text()==z)
            {
                markButtons(buttons,kol,i,j, z_ai);
                return 1;
            }
            if(j+4<kol && i+4<wr && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + (i+3) * kol+3]->text()==z && buttons[j + (i+4) * kol+4]->text()==z)
            {
                markButtons(buttons,kol,i,j, z_ai);
                return 1;
            }
            if(j-4>=0 && i-4>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i-3) * kol-3]->text()==z && buttons[j + (i-4) * kol-4]->text()==z)
            {
                markButtons(buttons,kol,i,j, z_ai);
                return 1;
            }
            if(j-4>=0 && i+4<wr && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i+3) * kol-3]->text()==z && buttons[j + (i+4) * kol-4]->text()==z)
            {
                markButtons(buttons,kol,i,j, z_ai);
                return 1;
            }
            if(j+4<kol && i-4>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + (i-3) * kol+3]->text()==z && buttons[j + (i-4) * kol+4]->text()==z)
            {
                markButtons(buttons,kol,i,j, z_ai);
                return 1;
            }
            if(i+4<wr && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()=="" && buttons[j + (i+3) * kol]->text()==z && buttons[j + (i+4) * kol]->text()==z)
            {
                markButtons(buttons,kol,i+2,j, z_ai);
                return 1;
            }
            if(j+4<kol && buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()=="" && buttons[j + i * kol+3]->text()==z && buttons[j + i * kol+4]->text()==z)
            {
                markButtons(buttons,kol,i,j+2, z_ai);
                return 1;
            }
            if(i+4<wr && j+4<=kol && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()=="" && buttons[j + (i+3) * kol+3]->text()==z && buttons[j + (i+4) * kol+4]->text()==z)
            {
                markButtons(buttons,kol,i+2,j+2, z_ai);
                return 1;
            }
            if(i+4<wr && j-4>=0 && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()=="" && buttons[j + (i+3) * kol-3]->text()==z && buttons[j + (i+4) * kol-4]->text()==z)
            {
                markButtons(buttons,kol,i+2,j-2, z_ai);
                return 1;
            }
            if(i+4<wr && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()=="" && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i+3) * kol]->text()==z && buttons[j + (i+4) * kol]->text()==z)
            {
                markButtons(buttons,kol,i+1,j, z_ai);
                return 1;
            }
            if(i+4<wr && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i+3) * kol]->text()=="" && buttons[j + (i+4) * kol]->text()==z)
            {
                markButtons(buttons,kol,i+3,j, z_ai);
                return 1;
            }
            if(j+4<kol && buttons[j + i * kol]->text()==z && buttons[j + (i) * kol+1]->text()=="" && buttons[j + (i) * kol+2]->text()==z && buttons[j + (i) * kol+3]->text()==z && buttons[j + (i) * kol+4]->text()==z)
            {
                markButtons(buttons,kol,i,j+1, z_ai);
                return 1;
            }
            if(j+4<kol && buttons[j + i * kol]->text()==z && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol+2]->text()==z && buttons[j + (i) * kol+3]->text()=="" && buttons[j + (i) * kol+4]->text()==z)
            {
                markButtons(buttons,kol,i,j+3, z_ai);
                return 1;
            }
            if(i+4<wr && j+4<kol && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()=="" && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + (i+3) * kol+3]->text()==z && buttons[j + (i+4) * kol+4]->text()==z)
            {
                markButtons(buttons,kol,i+1,j+1, z_ai);
                return 1;
            }
            if(i+4<wr && j-4>=0 &&  buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i+3) * kol-3]->text()=="" && buttons[j + (i+4) * kol-4]->text()==z)
            {
                markButtons(buttons,kol,i+3,j-3, z_ai);
                return 1;
            }
            if(i+4<wr && j-4>=0 && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()=="" && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i+3) * kol-3]->text()==z && buttons[j + (i+4) * kol-4]->text()==z)
            {
                markButtons(buttons,kol,i+1,j-1, z_ai);
                return 1;
            }
            if(i+4<wr && j+4<kol && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + (i+3) * kol+3]->text()=="" && buttons[j + (i+4) * kol+4]->text()==z)
            {
                markButtons(buttons,kol,i+3,j+3, z_ai);
                return 1;
            }
        }
    }
    return 0;
}

int AI::specialCase(QPushButton **buttons, const int kol, const int wr, QString z ,QString znak_ai)
{
    //z- znak gracza
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(i+3<wr && i-2>=0 && buttons[j + (i-2) * kol]->text()=="" && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z &&
                    buttons[j + (i+3) * kol]->text()=="" && buttons[j + (i+1) * kol]->text()==z  && buttons[j + i * kol]->text()=="")

            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(i-3>=0 && i+2<wr && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z &&
                    buttons[j + i * kol]->text()=="" && buttons[j + (i-3) * kol]->text()=="" && buttons[j + (i+2) * kol]->text()=="")
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && j-3>=0 && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol-2]->text()==z  &&
                    buttons[j + i * kol]->text()=="" && buttons[j + (i) * kol-3]->text()=="" && buttons[j + (i) * kol+2]->text()=="")
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-2>=0 && j+3<kol && buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol+2]->text()==z &&
                    buttons[j + i * kol]->text()=="" && buttons[j + (i) * kol-2]->text()=="" && buttons[j + (i) * kol+3]->text()=="")
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-2>=0 && j+3<kol && i+3<wr && i-2>=0 && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z &&
                    buttons[j + i * kol]->text()=="" && buttons[j + (i-2) * kol-2]->text()=="" && buttons[j + (i+3) * kol+3]->text()=="")
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-3>=0 && j+2<kol && i+2<wr && i-3>=0 && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z &&
                    buttons[j + i * kol]->text()=="" && buttons[j + (i+2) * kol+2]->text()=="" && buttons[j + (i-3) * kol-3]->text()=="")
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-3>=0 && j+2<kol && i+3<wr && i-2>=0 && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z &&
                    buttons[j + i * kol]->text()=="" && buttons[j + (i-2) * kol+2]->text()=="" && buttons[j + (i+3) * kol-3]->text()=="")
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-2>=0 && j+3<kol && i+2<wr && i-3>=0 && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z &&
                    buttons[j + i * kol]->text()=="" && buttons[j + (i+2) * kol-2]->text()=="" && buttons[j + (i-3) * kol+3]->text()=="")
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && i+2<wr && i-2>=0 && j-2>=0 && ((buttons[j + (i-1) * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                          buttons[j + (i-2) * kol]->text()=="" && buttons[j + (i+2) * kol]->text()=="" && buttons[j + i * kol-2]->text()=="" && buttons[j + i * kol+2]->text()=="")
                                                         || (buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                             buttons[j + (i-2) * kol+2]->text()=="" && buttons[j + (i+2) * kol-2]->text()=="" && buttons[j + (i-2) * kol-2]->text()=="" && buttons[j + (i+2) * kol+2]->text()=="")))
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && i+2<wr && i-2>=0 && j-3>=0 && ((buttons[j + (i-1) * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                          buttons[j + (i-2) * kol]->text()=="" && buttons[j + (i+2) * kol]->text()=="" && buttons[j + i * kol-3]->text()=="")
                                                         ||(buttons[j + (i-1) * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                            buttons[j + (i-2) * kol]->text()=="" && buttons[j + (i+2) * kol]->text()=="" && buttons[j + i * kol+3]->text()=="")))
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && i+3<wr && i-3>=0 && j-2>=0 && ((buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                          buttons[j + (i+3) * kol]->text()=="" && buttons[j + i * kol-2]->text()=="" && buttons[j + i * kol+2]->text()=="")
                                                         ||(buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                            buttons[j + (i-3) * kol]->text()=="" && buttons[j + i * kol-2]->text()=="" && buttons[j + i * kol+2]->text()=="")))
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && i+3<wr && j-3>=0 && ((buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                buttons[j + (i+3) * kol]->text()=="" &&  buttons[j + i * kol-3]->text()=="")
                                               ||(buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                  buttons[j + (i+3) * kol]->text()=="" && buttons[j + i * kol+3]->text()=="")))
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && i-3>=0 && j-3>=0 && ((buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                buttons[j + (i-3) * kol]->text()=="" && buttons[j + i * kol-3]->text()=="")
                                               ||(buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                  buttons[j + (i-3) * kol]->text()=="" &&  buttons[j + i * kol+3]->text()=="")))
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && j-3>=0 && i+3<wr && ((buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol-2]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                buttons[j + (i) * kol-3]->text()=="" && buttons[j + (i+3) * kol+3]->text()=="")
                                               ||(buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                  buttons[j + (i+3) * kol-3]->text()=="" && buttons[j + i * kol+3]->text()=="")))
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && j-3>=0 && i-3>=0 && ((buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol-2]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                buttons[j + (i) * kol-3]->text()=="" && buttons[j + (i-3) * kol+3]->text()=="")
                                               ||(buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                  buttons[j + (i-3) * kol-3]->text()=="" && buttons[j + i * kol+3]->text()=="")))
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && j-3>=0 && i+3<wr && i-3>=0 && ((buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                          buttons[j + (i+3) * kol-3]->text()=="" &&  buttons[j + (i-3) * kol]->text()=="")
                                                         ||(buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                            buttons[j + (i-3) * kol]->text()=="" && buttons[j + (i+3) * kol+3]->text()=="")))
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && j-3>=0 && i+3<wr && i-3>=0 && ((buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                          buttons[j + (i-3) * kol-3]->text()=="" &&  buttons[j + (i+3) * kol]->text()=="")
                                                         ||(buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                            buttons[j + (i+3) * kol]->text()=="" &&  buttons[j + (i-3) * kol+3]->text()=="")))
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && j-3>=0 && i+3<wr && i-3>=0 && ((buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                          buttons[j + (i-3) * kol-3]->text()=="" && buttons[j + (i+3) * kol]->text()=="")
                                                         ||(buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                            buttons[j + (i+3) * kol]->text()=="" &&  buttons[j + (i-3) * kol+3]->text()=="")))
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && j-3>=0 && i-3>=0 && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                    buttons[j + (i-3) * kol+3]->text()=="" && buttons[j + (i-3) * kol-3]->text()=="")
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && j-3>=0 && i+3<wr  && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                    buttons[j + (i+3) * kol-3]->text()=="" && buttons[j + (i+3) * kol+3]->text()=="")
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+3<kol && j-3>=0 && i+3<wr && i-3>=0 && ((buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                          buttons[j + (i-3) * kol-3]->text()=="" && buttons[j + (i+3) * kol-3]->text()=="")
                                                         ||(buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="" &&
                                                            buttons[j + (i+3) * kol+3]->text()=="" && buttons[j + (i-3) * kol+3]->text()=="")))
            {
                markButtons(buttons,kol,i,j, znak_ai);
                return 1;
            }
        }
    }
    return 0;
}
