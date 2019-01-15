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
            do
            {
                w_r=random(3,wr-4);
                k_r=random(3,kol-4);
            }
            while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x");
        }else
        {
            do
            {
                w_r=random(0,wr-1);
                k_r=random(0,kol-1);
            }
            while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x");
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
            w_r=random(w_ai-1,w_ai+1);
            k_r=random(k_ai-1,k_ai+1);
        }
        while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x");// || w_ai<0 || k_ai<0 || w_ai>wr || k_ai>kol );
        w_ai=w_r;
        k_ai=k_r;
        markButtons(buttons,kol,w_ai,k_ai,znak_ai);
        tmp++;
    }
    else
    {
        dir=0;
        if(win(buttons,kol,wr,znak_ai)==0) //do poprawy
        {
            if(specialCase(buttons,kol,wr,gracz,znak_ai)==0)
            {
                if(block(buttons,kol,wr,gracz,znak_ai)==0)
                {
                    if(specialCase(buttons,kol,wr,znak_ai,znak_ai)==0)
                    {
                        direction(buttons,kol,wr,gracz,znak_ai);
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

//wybiera najlepszy kierunek dla ai
int AI::direction(QPushButton **buttons,const int kol,const int wr,QString gracz,QString z)
{  
    // if(blokada==2) blokada=0;
    // temp_wier=0;
    //  temp_kolumn=0;
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(i+3<wr && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol]->text()==z && ((buttons[j + (i+2) * kol]->text()==z && buttons[j + (i+3) * kol]->text()==z) || buttons[j + (i+2) * kol]->text()==z))
            {
                markButtons2(buttons,kol,i,j, z);
                return 1;
            }
            if(i-3>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol]->text()==z && ((buttons[j + (i-2) * kol]->text()==z && buttons[j + (i-3) * kol]->text()==z) || buttons[j + (i-2) * kol]->text()==z))
            {
                markButtons2(buttons,kol,i,j, z);
                return 1;
            }
            if(j+3<kol && buttons[j + (i) * kol]->text()=="" && buttons[j + (i) * kol+1]->text()==z && ((buttons[j + (i) * kol+2]->text()==z && buttons[j + (i) * kol+3]->text()==z) || buttons[j + (i) * kol+2]->text()==z))
            {
                markButtons2(buttons,kol,i,j, z);
                return 1;
            }
            if(j-3>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i) * kol-1]->text()==z && ((buttons[j + (i) * kol-2]->text()==z && buttons[j + (i) * kol-3]->text()==z) || buttons[j + (i) * kol-2]->text()==z))
            {
                markButtons2(buttons,kol,i,j, z);
                return 1;
            }
            if(j+3<kol && i+3<wr && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol+1]->text()==z && ((buttons[j + (i+2) * kol+2]->text()==z && buttons[j + (i+3) * kol+3]->text()==z) || buttons[j + (i+2) * kol+2]->text()==z))
            {
                markButtons2(buttons,kol,i,j, z);
                return 1;
            }
            if(j-3>=0 && i-3>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol-1]->text()==z && ((buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i-3) * kol-3]->text()==z) || buttons[j + (i-2) * kol-2]->text()==z))
            {
                markButtons2(buttons,kol,i,j, z);
                return 1;
            }
            if(j-3>=0 && i+3<wr && buttons[j + (i) * kol]->text()=="" && buttons[j + (i+1) * kol-1]->text()==z && ((buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i+3) * kol-3]->text()==z) || buttons[j + (i+2) * kol-2]->text()==z))
            {
                markButtons2(buttons,kol,i,j, z);
                return 1;
            }
            if(j+3<kol && i-3>=0 && buttons[j + (i) * kol]->text()=="" && buttons[j + (i-1) * kol+1]->text()==z && ((buttons[j + (i-2) * kol+2]->text()==z && buttons[j + (i-3) * kol+3]->text()==z) || buttons[j + (i-2) * kol+2]->text()==z))
            {
                markButtons2(buttons,kol,i,j, z);
                return 1;
            }
        }
    }
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            if(j>1 && i>1 && i<wr-2 && j<kol-2 && buttons[j + (i) * kol]->text()==z)
            {
                do
                {
                    QTime time = QTime::currentTime();
                    qsrand(static_cast<uint>(time.msec()));

                    w_r=random(i-1,i+1);
                    k_r=random(j-1,j+1);
                }
                while(buttons[w_r*kol+k_r]->text()=="o" || buttons[w_r*kol+k_r]->text()=="x");
                markButtons2(buttons,kol,w_r,k_r, z);
                qDebug()<<"Losuje";
                return 1;
            }


        }
    }

}

int AI::markButtons(QPushButton **buttons,const int kol,int i,int j,QString znak)
{
    if(buttons[(i)*kol+j]->text()=="")
    {
        buttons[(i)*kol+j]->setText(znak);
        buttons[(i)*kol+j]->setStyleSheet("QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
        buttons[(i)*kol+j]->setDisabled(1);
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

                if(i+3<=wr && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z) //pion gora
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
                if(i-3>=0 && buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z) //pion dół
                    if( buttons[j + (i-3) * kol]->text()=="")
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

int AI::specialCase(QPushButton **buttons, const int kol, const int wr, QString z ,QString znak_ai)
{
    //z- znak gracza
    for(int i=0;i<wr;i++)
    {
        for(int j=0;j<kol;j++)
        {
            /*if(i+4<wr && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()=="" && buttons[j + (i+3) * kol]->text()==z && buttons[j + (i+4) * kol]->text()==z)
            {
                markButtons2(buttons,kol,i+2,j, znak_ai);
                return 1;
            }
            if(j+4<kol && buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()=="" && buttons[j + i * kol+3]->text()==z && buttons[j + i * kol+4]->text()==z)
            {
                markButtons2(buttons,kol,i,j+2, znak_ai);
                return 1;
            }
            if(i+4<wr && j+4<=kol && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()=="" && buttons[j + (i+3) * kol+3]->text()==z && buttons[j + (i+4) * kol+4]->text()==z)
            {
                markButtons2(buttons,kol,i+2,j+2, znak_ai);
                return 1;
            }
            if(i+4<wr && j-4>=0 && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()=="" && buttons[j + (i+3) * kol-3]->text()==z && buttons[j + (i+4) * kol-4]->text()==z)
            {
                markButtons2(buttons,kol,i+2,j-2, znak_ai);
                return 1;
            }
            if(i+4<wr && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()=="" && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i+3) * kol]->text()==z && buttons[j + (i+4) * kol]->text()==z)
            {
                markButtons2(buttons,kol,i+1,j, znak_ai);
                return 1;
            }
            if(i+4<wr && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i+3) * kol]->text()=="" && buttons[j + (i+4) * kol]->text()==z)
            {
                markButtons2(buttons,kol,i+3,j, znak_ai);
                return 1;
            }
            if(j+4<kol && buttons[j + i * kol]->text()==z && buttons[j + (i) * kol+1]->text()=="" && buttons[j + (i) * kol+2]->text()==z && buttons[j + (i) * kol+3]->text()==z && buttons[j + (i) * kol+4]->text()==z)
            {
                markButtons2(buttons,kol,i,j+1, znak_ai);
                return 1;
            }
            if(j+4<kol && buttons[j + i * kol]->text()==z && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol+2]->text()==z && buttons[j + (i) * kol+3]->text()=="" && buttons[j + (i) * kol+4]->text()==z)
            {
                markButtons2(buttons,kol,i,j+3, znak_ai);
                return 1;
            }
            if(i+4<wr && j+4<kol && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()=="" && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + (i+3) * kol+3]->text()==z && buttons[j + (i+4) * kol+4]->text()==z)
            {
                markButtons2(buttons,kol,i+1,j+1, znak_ai);
                return 1;
            }
            if(i+4<wr && j-4>=0 &&  buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i+3) * kol-3]->text()=="" && buttons[j + (i+4) * kol-4]->text()==z)
            {
                markButtons2(buttons,kol,i+3,j-3, znak_ai);
                return 1;
            }
            if(i+4<wr && j-4>=0 && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()=="" && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i+3) * kol-3]->text()==z && buttons[j + (i+4) * kol-4]->text()==z)
            {
                markButtons2(buttons,kol,i+1,j-1, znak_ai);
                return 1;
            }
            if(i+4<wr && j+4<kol && buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + (i+3) * kol+3]->text()=="" && buttons[j + (i+4) * kol+4]->text()==z)
            {
                markButtons2(buttons,kol,i+3,j+3, znak_ai);
                return 1;
            }*/
            if(i+2<wr && i-1>0 && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z  && buttons[j + i * kol]->text()=="")

            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(i-2>0 && i+1<wr && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z &&  buttons[j + i * kol]->text()=="")
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && j-2>0 && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol-2]->text()==z  && buttons[j + i * kol]->text()=="")
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-1>0 && j+2<kol && buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol+1]->text()==z && buttons[j + (i) * kol+2]->text()==z &&  buttons[j + i * kol]->text()=="")
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-1>0 && j+2<kol && i+2<wr && i-1>0 && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z &&  buttons[j + i * kol]->text()=="")
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-2>0 && j+1<kol && i+1<wr && i-2>0 && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z &&  buttons[j + i * kol]->text()=="")
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-2>0 && j+1<kol && i+2<wr && i-1>0 && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z &&  buttons[j + i * kol]->text()=="")
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j-1>0 && j+2<kol && i+2<wr && i-2>0 && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z &&  buttons[j + i * kol]->text()=="")
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+1<kol && i+1<wr && i-1>=0 && j-1>=0 && ((buttons[j + (i-1) * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol]->text()=="")
                                                         || (buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + i * kol]->text()=="")))
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && i+1<wr && i-1>=0 && j-2>=0 && ((buttons[j + (i-1) * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z && buttons[j + i * kol]->text()=="")
                                                         ||(buttons[j + (i-1) * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z && buttons[j + i * kol]->text()=="")))
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && i+2<wr && j-2>=0 && ((buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z && buttons[j + i * kol]->text()=="")
                                               ||(buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z && buttons[j + i * kol]->text()=="")))
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && i-2>=0 && j-2>=0 && ((buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z && buttons[j + i * kol]->text()=="")
                                               ||(buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z && buttons[j + i * kol]->text()=="")))
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && j-2>=0 && i+2<wr && ((buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol-2]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="")
                                               ||(buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z && buttons[j + i * kol]->text()=="")))
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && j-2>=0 && i-2>=0 && ((buttons[j + (i) * kol-1]->text()==z && buttons[j + (i) * kol-2]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="")
                                               ||(buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z && buttons[j + i * kol]->text()=="")))
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && j-2>=0 && i+2<wr && i-2>=0 && ((buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + i * kol]->text()=="")
                                                         ||(buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="")))
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && j-2>=0 && i+2<wr && i-2>=0 && ((buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + i * kol]->text()=="")
                                                         ||(buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="")))
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && j-2>=0 && i+2<wr && i-2>=0 && ((buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + i * kol]->text()=="")
                                                         ||(buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="")))
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && j-2>=0 && i-2>=0 && buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="")
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && j-2>=0 && i+2<wr  && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="")
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
            if(j+2<kol && j-2>=0 && i+2<wr && i-2>=0 && ((buttons[j + (i-1) * kol-1]->text()==z && buttons[j + (i-2) * kol-2]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z && buttons[j + i * kol]->text()=="")
                                                         ||(buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z && buttons[j + (i-1) * kol+1]->text()==z && buttons[j + (i-2) * kol+2]->text()==z && buttons[j + i * kol]->text()=="")))
            {
                markButtons2(buttons,kol,i,j, znak_ai);
                return 1;
            }
        }
    }
    return 0;
}
