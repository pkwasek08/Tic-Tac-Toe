#include "ai.h"
#include <QTime>
#include <qglobal.h>
/*
  dir = 1 poziom w lewo
        2 poziom w prawo
        3 pion gora
        4 pion dol
        5 skos
        6 skos
*/

AI::AI()
{
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
        if(wr/2>3 && kol/2>3)
        {
            w_r=random(3,wr-4);
            k_r=random(3,kol-4);
        }else
        {
            w_r=random(0,wr-1);
            k_r=random(0,kol-1);
        }
        buttons[k_r + w_r * kol]->setText(znak_ai);
        buttons[k_r + w_r * kol]->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
        buttons[k_r + w_r * kol]->setDisabled(1);
        w_ai=w_r;
        k_ai=k_r;
        tmp++;
    }else if(tmp==1) //2 ruch
    {
        do
        {
            QTime time = QTime::currentTime();
            qsrand(static_cast<uint>(time.msec()));
            if(w_ai==0) w_ai++;
            if(k_ai==0) k_ai++;
            if(w_ai==wr) w_ai--;
            if(k_ai==kol) k_ai--;
            w_r=random(w_ai-1,w_ai+1);
            k_r=random(k_ai-1,k_ai+1);
        }
        while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x"); //w_ai<0 || k_ai<0 || w_ai>wr || k_ai>kol ||
        w_ai=w_r;
        k_ai=k_r;
        markButtons(buttons,kol,0,0,znak_ai);
        tmp++;
    }
    else
    {
        dir=0;
        if(win(buttons,kol,wr,znak_ai)==0) //do poprawy
        {
            if(block(buttons,kol,wr,gracz,znak_ai)==0)
            {
                dir=direction(buttons,kol,wr,gracz,znak_ai);
                if(dir==1)
                {
                    markButtons(buttons,kol,0,temp_kolumn,znak_ai);
                }
                else if(dir==2)
                {
                    markButtons(buttons,kol,0,temp_kolumn,znak_ai);
                }
                else if(dir==3)
                {
                    markButtons(buttons,kol,temp_wier,0,znak_ai);
                }
                else if(dir==4)
                {
                    markButtons(buttons,kol,temp_wier,0,znak_ai);
                }
                else if(dir==5)
                {
                    markButtons(buttons,kol,temp_wier,temp_kolumn,znak_ai);
                }
                else if(dir==6)
                {
                    markButtons(buttons,kol,temp_wier,temp_kolumn,znak_ai);
                }
                else if(dir==7)
                {
                    do
                    {
                        QTime time = QTime::currentTime();
                        qsrand(static_cast<uint>(time.msec()));
                        if(w_ai==0) w_ai++;
                        if(k_ai==0) k_ai++;
                        if(w_ai==wr) w_ai--;
                        if(k_ai==kol) k_ai--;
                        w_r=random(w_ai-1,w_ai+1);
                        k_r=random(k_ai-1,k_ai+1);
                    }
                    while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x" || w_r<0
                          || k_r<0 || w_r>wr || k_r>kol);
                    w_ai=w_r;
                    k_ai=k_r;
                    markButtons(buttons,kol,0,0,znak_ai);
                    blokada=0;
                    // tmp=1;
                }
                else if(dir==8)
                {
                    do
                    {
                        if(wr/2>3 && kol/2>3)
                        {
                            w_r=random(1,wr-1);
                            k_r=random(1,kol-1);
                        }else
                        {
                            w_r=random(0,wr-1);
                            k_r=random(0,kol-1);
                        }
                    }
                    while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x" || w_r<0
                          || k_r<0 || w_r>wr || k_r>kol);
                    buttons[k_r + w_r * kol]->setText(znak_ai);
                    buttons[k_r + w_r * kol]->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
                    buttons[k_r + w_r * kol]->setDisabled(1);
                    w_ai=w_r;
                    k_ai=k_r;
                }
            }
        }
    }
}

int AI::random(int nMin, int nMax)  //losuje
{
    return qrand() % (nMax - nMin + 1 ) + nMin;
}

//wybiera najlepszy kierunek dla ai
int AI::direction(QPushButton **but,const int kol,const int wr,QString gracz,QString znak_ai)
{  
    if(blokada==2) blokada=0;
    temp_wier=0;
    temp_kolumn=0;
    if(w_ai-1>=0 && w_ai+1<=wr && k_ai-1>=0 && k_ai+1<=kol && but[(w_ai-1)*kol+k_ai-1]->text()!="" && but[w_ai*kol+k_ai-1]->text()!="" && but[(w_ai-1)*kol+k_ai]->text()!="" && but[(w_ai+1)*kol+k_ai]->text()!="" &&
            but[(w_ai-1)*kol+k_ai+1]->text()!="" && but[(w_ai+1)*kol+k_ai-1]->text()!="" && but[(w_ai+1)*kol+k_ai+1]->text()!="" && but[w_ai*kol+k_ai+1]->text()!="")
    {
        return 8;
    }
    else if(k_ai-1>=0 && but[w_ai*kol+k_ai]->text()==znak_ai && but[w_ai*kol+k_ai-1]->text()==znak_ai) //poziom lewy
    {
        while(but[w_ai*kol+k_ai+temp_kolumn]->text()==znak_ai)
        { temp_kolumn--; }
        if(but[w_ai*kol+k_ai+temp_kolumn]->text()==gracz)
        {
            temp_kolumn=1;
            blokada++;
        }
        if(blokada==2) return 7;
        if(k_ai>(w_ai+1)*kol-(w_ai*kol+k_ai+temp_kolumn) &&  but[w_ai*kol+k_ai+temp_kolumn]->text()=="")
        {
            return 1;
        }
        else if(but[w_ai*kol+k_ai+temp_kolumn]->text()=="") return 2;
    }
    else if(k_ai+1<=kol && but[w_ai*kol+k_ai]->text()==znak_ai && but[w_ai*kol+k_ai+1]->text()==znak_ai) //poziom prawy
    {
        while(but[w_ai*kol+k_ai+temp_kolumn]->text()==znak_ai)
            temp_kolumn++;
        //if(but[w_ai*kol+k_ai+temp_wier+1]->text()=="o" && but[w_ai*kol+k_ai-1]->text()=="o") return 7;
        if(but[w_ai*kol+k_ai+temp_kolumn]->text()==gracz)
        {
            temp_kolumn=-1;
            blokada++;
        }
        if(blokada==2) return 7;
        if(k_ai>(w_ai+1)*kol-(w_ai*kol+k_ai+temp_kolumn) &&  but[w_ai*kol+k_ai+temp_kolumn]->text()=="" )
        {
            return 1;
        }
        else if(but[w_ai*kol+k_ai+temp_kolumn]->text()=="") return 2;
    }
    else if(w_ai-1>=0 && but[w_ai*kol+k_ai]->text()==znak_ai && but[(w_ai-1)*kol+k_ai]->text()==znak_ai) //pion gora
    {
        while(but[(w_ai+temp_wier)*kol+k_ai]->text()==znak_ai)
        { temp_wier--; }
        if(but[(w_ai+temp_wier)*kol+k_ai]->text()==gracz)
        {
            temp_wier=1;
            blokada++;
        }
        if(blokada==2) return 7;
        if(w_ai>wr-(w_ai+temp_wier) &&  but[(w_ai+temp_wier)*kol+k_ai]->text()=="")
        {
            return 4;
        }
        else if(but[(w_ai+temp_wier)*kol+k_ai]->text()=="") return 3;
    }
    else if(w_ai+1<=wr && but[w_ai*kol+k_ai]->text()==znak_ai && but[(w_ai+1)*kol+k_ai]->text()==znak_ai) //pion dol
    {
        while(but[(w_ai+temp_wier)*kol+k_ai]->text()==znak_ai)
        {temp_wier++; }
        if(but[(w_ai+temp_wier)*kol+k_ai]->text()==gracz)
        {
            temp_wier=-1;
            blokada++;
        }
        if(blokada==2) return 7;
        if(w_ai>wr-(w_ai+temp_wier) &&  but[(w_ai+temp_wier)*kol+k_ai]->text()=="" )
        {
            return 3;
        }
        else if(but[(w_ai+temp_wier)*kol+k_ai]->text()=="") return 4;
    }
    else if(w_ai>=wr/2)
    {
        //skos 1 wariant
        if(k_ai-1>=0 && but[w_ai*kol+k_ai]->text()==znak_ai && but[(w_ai-1)*kol+k_ai-1]->text()==znak_ai)
        {
            while(but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()==znak_ai)
            {
                temp_wier--;
                temp_kolumn--;
            }
            if(w_ai+1<=wr && but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()==gracz)
            {
                temp_wier=1;
                temp_kolumn=1;
                blokada++;
            }
            if(blokada==2) return 7;
            if(k_ai+1<=kol && k_ai + (w_ai+temp_wier) * kol+temp_kolumn>=(w_ai+temp_wier)*kol && k_ai + (w_ai+temp_wier) * kol+temp_kolumn<(w_ai+(temp_kolumn-1))*kol && but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()=="")
            {
                return 5;
            }
            else if(k_ai+1<=kol && k_ai + (w_ai+temp_wier) * kol+temp_kolumn>=(w_ai+temp_wier)*kol && k_ai + (w_ai+temp_wier) * kol+temp_kolumn<(w_ai+(temp_kolumn+1))*kol && but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()=="") return 6;
        } //skos 2 wariant
        else if(w_ai+1<=wr && k_ai+1<=kol && k_ai-1>=0 && but[w_ai*kol+k_ai]->text()==znak_ai && but[(w_ai-1)*kol+k_ai+1]->text()==znak_ai)
        {
            while(but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()==znak_ai)
            {
                temp_wier--;
                temp_kolumn++;
            }
            if(but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()==gracz)
            {
                temp_wier=1;
                temp_kolumn=-1;
                blokada++;
            }
            if(blokada==2) return 7;
            if(k_ai + (w_ai+temp_wier) * kol+temp_kolumn>=(w_ai+temp_wier)*kol && k_ai + (w_ai+temp_wier) * kol+temp_kolumn<(w_ai+(temp_kolumn-1))*kol &&  but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()=="")
            {
                return 5;
            }
            else if(k_ai + (w_ai+temp_wier) * kol+temp_kolumn>=(w_ai+temp_wier)*kol && k_ai + (w_ai+temp_wier) * kol+temp_kolumn<(w_ai+(temp_kolumn+1))*kol && but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()=="") return 6;
        }
    }
    else if(w_ai<=wr/2)
    {
        if(w_ai-1>=0 && k_ai+1<=kol && k_ai-1>=0 && but[w_ai*kol+k_ai]->text()==znak_ai && but[(w_ai+1)*kol+k_ai+1]->text()==znak_ai) //skos 1 wariant
        {
            while(but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()==znak_ai)
            {
                temp_wier++;
                temp_kolumn++;
            }
            if(but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()==gracz)
            {
                temp_wier=-1;
                temp_kolumn=-1;
                blokada++;
            }
            if(blokada==2) return 7;
            if(k_ai + (w_ai+temp_wier) * kol+temp_kolumn>=(w_ai+temp_wier)*kol && k_ai + (w_ai+temp_wier) * kol+temp_kolumn<(w_ai+(temp_kolumn+1))*kol && but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()=="")
            {
                return 5;
            }
            else if(k_ai + (w_ai+temp_wier) * kol+temp_kolumn>=(w_ai+temp_wier)*kol && k_ai + (w_ai+temp_wier) * kol+temp_kolumn<(w_ai+(temp_kolumn-1))*kol && but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()=="") return 6;
        }
        else if(w_ai-1>=0 && k_ai+1<=kol && k_ai-1>=0 && but[w_ai*kol+k_ai]->text()==znak_ai && but[(w_ai+1)*kol+k_ai-1]->text()==znak_ai) //skos 2 wariant
        {
            while(but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()==znak_ai)
            {
                temp_wier++;
                temp_kolumn--;
            }
            if(but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()==gracz)
            {
                temp_wier=-1;
                temp_kolumn=1;
                blokada++;
            }
            if(blokada==2) return 7;
            if(k_ai + (w_ai+temp_wier) * kol+temp_kolumn>=(w_ai+temp_wier)*kol && k_ai + (w_ai+temp_wier) * kol+temp_kolumn<(w_ai+(temp_kolumn+1))*kol && but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()=="")
            {
                return 5;
            }
            else if(k_ai + (w_ai+temp_wier) * kol+temp_kolumn>=(w_ai+temp_wier)*kol && k_ai + (w_ai+temp_wier) * kol+temp_kolumn<(w_ai+(temp_kolumn-1))*kol && but[(w_ai+temp_wier)*kol+k_ai+temp_kolumn]->text()=="") return 6;
        }
    }
    if(w_ai-1>=0 && w_ai+1<=wr && k_ai-1>=0 && k_ai+1<=kol && (but[(w_ai-1)*kol+k_ai-1]->text()=="" || but[w_ai*kol+k_ai-1]->text()=="" || but[(w_ai-1)*kol+k_ai]->text()=="" || but[(w_ai+1)*kol+k_ai]->text()=="" ||
                                                               but[(w_ai-1)*kol+k_ai+1]->text()=="" || but[(w_ai+1)*kol+k_ai-1]->text()=="" || but[(w_ai+1)*kol+k_ai+1]->text()=="" || but[w_ai*kol+k_ai+1]->text()==""))
    {
        return 7;
    }
    return 8;
}

int AI::markButtons(QPushButton **buttons,const int kol,int i,int j,QString znak)
{
    if(buttons[(w_ai+i)*kol+k_ai+j]->text()=="")
    {
        buttons[(w_ai+i)*kol+k_ai+j]->setText(znak);
        buttons[(w_ai+i)*kol+k_ai+j]->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
        buttons[(w_ai+i)*kol+k_ai+j]->setDisabled(1);
        w_ai=w_ai+i;
        k_ai=k_ai+j;
        return 1;
    }
    return 0;
}

void AI::markButtons2(QPushButton **buttons,const int kol,int i,int j,QString znak)
{
    if(buttons[i*kol+j]->text()=="")
    {
        buttons[i*kol+j]->setText(znak);
        buttons[i*kol+j]->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
        buttons[i*kol+j]->setDisabled(1);
    }
}

int AI::block(QPushButton **buttons, const int kol, const int wr, QString z ,QString znak_ai)
{
     //z- znak gracza
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(i<=wr/2)
            {
                if( buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z) //pion gora
                    if(buttons[j + (i+3) * kol]->text()=="")
                    {
                        markButtons2(buttons,kol,i+3,j, znak_ai);
                        return 1;
                    }
                    else if(i-1>=0 && buttons[j + (i-1) * kol]->text()=="")
                    {
                        markButtons2(buttons,kol,i-1,j, znak_ai);
                        return 1;
                    }
                //SKOS 1 WARIANT
                if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z)
                    if(j-3>=0 && j + (i+3) * kol-3>=(i+3)*kol && j + (i+3) * kol-3<=(i+4)*kol && buttons[j + (i+3) * kol-3]->text()=="")
                    {
                        markButtons2(buttons,kol,i+3,j-3, znak_ai);
                        return 1;
                    }
                    else if(j+1<=kol && i-1>=0 && j + (i-1) * kol+1>=(i-1)*kol && j + (i-1) * kol+1<=(i)*kol && buttons[j + (i-1) * kol+1]->text()=="")
                    {
                        markButtons2(buttons,kol,i-1,j+1, znak_ai);
                        return 1;
                    }
                //SKOS 2 WARIANT
                if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z)
                {

                    if(j+3<=kol && j + (i+3) * kol+3>=(i+3)*kol && j + (i+3) * kol+3<(i+3)*kol+kol-1 && buttons[j + (i+3) * kol+3]->text()=="")
                    {
                        markButtons2(buttons,kol,i+3,j+3, znak_ai);

                        return 1;
                    }
                    else if(i-1>=0 && j-1>=0 && j + (i-1) * kol-1>=(i-2)*kol && j + (i-1) * kol-1<=(i-1)*kol+kol-1 && buttons[j + (i-1) * kol-1]->text()=="")
                    {
                        markButtons2(buttons,kol,i-1,j-1, znak_ai);
                        return 1;
                    }
                }
            }
            else if(i>=wr/2)
            {
                if(buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z) //pion dół
                    if(i-3>=0 && buttons[j + (i-3) * kol]->text()=="")
                    {
                        markButtons2(buttons,kol,i-3,j, znak_ai);
                        return 1;
                    }
                    else if(i+1<=wr && buttons[j + (i+1) * kol]->text()=="")
                    {
                        markButtons2(buttons,kol,i+1,j, znak_ai);
                        return 1;
                    }
                //skos 1 wariant
                if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z)
                {
                    if(j-3<=kol && j + (i-3) * kol-3>=(i-3)*kol && j + (i-3) * kol-3<(i-4)*kol && buttons[j + (i-3) * kol-3]->text()=="")
                    {
                        markButtons2(buttons,kol,i-3,j-3, znak_ai);
                        return 1;
                    }
                    else if(j+1<=kol && i+1<=wr && j + (i+1) * kol+1>=(i+1)*kol && j + (i+1) * kol+1<=(i)*kol && buttons[j + (i+1) * kol+1]->text()=="")
                    {
                        markButtons2(buttons,kol,i+1,j+1, znak_ai);
                        return 1;
                    }
                }
                // skos 2 wariant
                if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)+1]->text()==z && buttons[(j + (i-2) * kol)+2]->text()==z)
                {
                    if(j+3<=kol && j + (i-3) * kol+3>=(i-3)*kol && j + (i-3) * kol+3<(i-4)*kol && buttons[j + (i-3) * kol+3]->text()=="")
                    {
                        markButtons2(buttons,kol,i-3,j+3, znak_ai);
                        return 1;
                    }
                    else if(i+1<=wr && j-1>=kol && j + (i+1) * kol-1>=(i+1)*kol && j + (i+1) * kol-1<=(i)*kol && buttons[j + (i+1) * kol-1]->text()=="")
                    {
                        markButtons2(buttons,kol,i+1,j-1, znak_ai);
                        return 1;
                    }
                }
            }
            if(j<=kol/2)
            {
                if(buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z) //poziom lewy
                    if(j+3<=kol && buttons[j + i * kol+3]->text()=="")
                    {
                        markButtons2(buttons,kol,i,j+3, znak_ai);
                        return 1;
                    }
                    else if(j-1>=0 && buttons[j + i * kol-1]->text()=="")
                    {
                        markButtons2(buttons,kol,i,j-1, znak_ai);
                        return 1;
                    }
            }
            else if(j>kol/2)
            {
                if(buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z) //poziom prawy
                    if(j-3>=0 && buttons[j + i * kol-3]->text()=="")
                    {
                        markButtons2(buttons,kol,i,j-3, znak_ai);
                        return 1;
                    }
                    else if(j+1<=kol && buttons[j + i * kol+1]->text()=="")
                    {
                        markButtons2(buttons,kol,i,j+1, znak_ai);
                        return 1;
                    }
            }
        }
    }
    return 0;
}

int AI::win(QPushButton **buttons, const int kol, const int wr, QString z)
{
    //z - znak ai
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            {
                if(i<=wr/2)
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z &&
                            buttons[j + (i+3) * kol]->text()==z) //pion gora
                        if(i-1>=0 && buttons[j + (i-1) * kol]->text()=="")
                        {
                            markButtons2(buttons,kol,i-1,j,z);
                            return 1;
                        } else if(i+4<=wr && buttons[j + (i+4) * kol]->text()=="")
                        {
                            markButtons2(buttons,kol,i+4,j,z);
                            return 1;
                        }

                    //skosy górna część
                    if(j + (i+4) * kol-4>=(i+4)*kol && j + (i+4) * kol-4<(i+5)*kol) // skos 1 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z &&
                                buttons[j + (i+3) * kol-3]->text()==z)
                        {
                            if(i-1>=0 && j+1<=kol && buttons[j + (i-1) * kol+1]->text()=="")
                            {
                                markButtons2(buttons,kol,i-1,j+1,z);
                                return 1;
                            } else if(i+4<=wr && j-4>=0 && buttons[j + (i+4) * kol -4]->text()=="")
                            {
                                markButtons2(buttons,kol,i+4,j-4,z);
                                return 1;
                            }
                        }
                    }
                    if(j + (i+4) * kol+4<(i+5)*kol && j + (i+4) * kol+4>=(i+4)*kol) // skos 2 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z &&
                                buttons[j + (i+3) * kol+3]->text()==z)
                        {
                            if(i-1>=0 && j-1>=0 && buttons[j + (i-1) * kol-1]->text()=="")
                            {
                                markButtons2(buttons,kol,i-1,j-1,z);
                                return 1;
                            } else if(i+4<=wr && j+4<=kol && buttons[j + (i+4) * kol +4]->text()=="")
                            {
                                markButtons2(buttons,kol,i+4,j+4,z);
                                return 1;
                            }
                        }
                    }
                }
                else if(i>=wr/2)
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z &&
                            buttons[j + (i-3) * kol]->text()==z)//pion dol
                    {
                        if(i+1<=kol && buttons[j + (i+1) * kol]->text()=="")
                        {
                            markButtons2(buttons,kol,i+1,j,z);
                            return 1;
                        } else if(i-4>=0 && buttons[j + (i-4) * kol]->text()=="")
                        {
                            markButtons2(buttons,kol,i-4,j,z);
                            return 1;
                        }
                    }
                    //skosy dolna cześć
                    if(j + (i-4) * kol-4>=(i-4)*kol && j + (i-4) * kol-4<(i-5)*kol) //skos 1 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z &&
                                buttons[(j + (i-3) * kol)-3]->text()==z)
                        {
                            if(i+1<=wr && j+1<=kol && buttons[j + (i+1) * kol+1]->text()=="")
                            {
                                markButtons2(buttons,kol,i+1,j+1,z);
                                return 1;
                            } else if(i-4>=0 && j-4>=0 && buttons[j + (i-4) * kol -4]->text()=="")
                            {
                                markButtons2(buttons,kol,i-4,j-4,z);
                                return 1;
                            }
                        }
                    }
                    if((j + (i-4) * kol)+4>=(i-4)*kol && (j + (i-4) * kol)+4<(i-5)*kol) //skos 2 wariant
                    {
                        if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)+1]->text()==z && buttons[(j + (i-2) * kol)+2]->text()==z &&
                                buttons[(j + (i-3) * kol)+3]->text()==z)
                        {
                            if(i+1<=wr && j-1>=0 && buttons[j + (i+1) * kol-1]->text()=="")
                            {
                                markButtons2(buttons,kol,i+1,j-1,z);
                                return 1;
                            } else if(j+4<=kol && i-4>=0 && buttons[j + (i-4) * kol +4]->text()=="")
                            {
                                markButtons2(buttons,kol,i-4,j+4,z);
                                return 1;
                            }
                        }
                    }
                }
                if(j<=kol/2)
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z &&
                            buttons[j + i * kol+3]->text()==z)//poziom lewy
                    {
                        if(j+4<=kol && buttons[j + i * kol+4]->text()=="")
                        {
                            markButtons2(buttons,kol,i,j+4,z);
                            return 1;
                        } else if(i-1>=0 && buttons[j + i* kol -1]->text()=="")
                        {
                            markButtons2(buttons,kol,i,j-1,z);
                            return 1;
                        }
                    }
                }
                else if(j>kol/2)
                    if(buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z &&
                            buttons[j + i * kol-3]->text()==z)//poziom prawy
                    {
                        if(j-4>=0 && buttons[j + i * kol-4]->text()=="")
                        {
                            markButtons2(buttons,kol,i,j-4,z);
                            return 1;
                        } else if(i+1<=kol && buttons[j + i* kol +1]->text()=="")
                        {
                            markButtons2(buttons,kol,i,j+1,z);
                            return 1;
                        }
                    }
            }
        }
    }
    return 0;
}
