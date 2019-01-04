#include "ai.h"
#include <random>
#include <QRandomGenerator>
#include <qglobal.h>
/*
  dir = 1 poziom w lewo
        2 poziom w prawo
        3 pion gora
        4 pion dol
*/

AI::AI()
{

}

void AI::choosebutton(QPushButton **buttons,const int kol,const int wr,QString znak)
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
        buttons[k_r + w_r * kol]->setText(znak);
        buttons[k_r + w_r * kol]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
        buttons[k_r + w_r * kol]->setDisabled(1);
        tmp++;
    }else if(tmp==1) //2 ruch
    {
        do
        {
            w_ai=random(w_r-1,w_r+1);
           // w_ai=w_r;
            k_ai=random(k_r-1,k_r+1);
            //k_ai=k_r;
        }
        while(buttons[w_ai*kol+k_ai]->text()=="o" || buttons[w_ai*kol+k_ai]->text()=="x"); //w_ai<0 || k_ai<0 || w_ai>wr || k_ai>kol ||
        markButtons(buttons,kol,wr,0,0,znak);
        w_r=w_ai;
        k_r=k_ai;
        tmp++;
    }
    else
    {
        dir=0;
        if(block(buttons,kol,wr,znak)==0)
        {
            dir=direction(buttons,kol,wr,znak);
            if(dir==1)
            {
                markButtons(buttons,kol,wr,0,temp_kolumn,znak);
            }
            else if(dir==2)
            {
                markButtons(buttons,kol,wr,0,temp_kolumn,znak);
            }
            else if(dir==3)
            {
                markButtons(buttons,kol,wr,temp_wier,0,znak);
            }
            else if(dir==4)
            {
                markButtons(buttons,kol,wr,temp_wier,0,znak);
            }
            else if(dir==7)
            {
                do
                {
                    w_ai=random(w_r-1,w_r+1);
                    //w_ai=w_r;
                    k_ai=random(k_r-1,k_r+1);
                    // k_ai=k_r;
                }
                while(buttons[w_ai*kol+k_ai]->text()=="o" || buttons[w_ai*kol+k_ai]->text()=="x"); //w_ai<0 || k_ai<0 || w_ai>wr || k_ai>kol ||
                //direction(buttons,kol,wr,znak);
                markButtons(buttons,kol,wr,temp_wier,temp_kolumn,znak);
                blokada=0;
            }
        }
    }


}


int AI::random(int nMin, int nMax)
{
    //  srand(time(0));
    qsrand(qrand());
    //  return bounded(nMin,nMax);
    return qrand() % (nMax - nMin + 1 ) + nMin;
}

int AI::direction(QPushButton **but,const int kol,const int wr,QString znak)
{  
    temp_wier=0;
    temp_kolumn=0;
    if(but[w_ai*kol+k_ai]->text()=="x" && but[w_ai*kol+k_ai-1]->text()=="x") //poziom lewy
    {
        while(but[w_ai*kol+k_ai+temp_kolumn]->text()=="x")
            temp_kolumn--;
        //if(but[w_ai*kol+k_ai+temp_wier-1]->text()=="o" && but[w_ai*kol+k_ai+1]->text()=="o") return 7;
        if(but[w_ai*kol+k_ai+temp_kolumn]->text()=="o")
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
    else if(but[w_ai*kol+k_ai]->text()=="x" && but[w_ai*kol+k_ai+1]->text()=="x") //poziom prawy
    {
        while(but[w_ai*kol+k_ai+temp_kolumn]->text()=="x")
            temp_kolumn++;
        //if(but[w_ai*kol+k_ai+temp_wier+1]->text()=="o" && but[w_ai*kol+k_ai-1]->text()=="o") return 7;
        if(but[w_ai*kol+k_ai+temp_kolumn]->text()=="o")
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
    else if(but[w_ai*kol+k_ai]->text()=="x" && but[(w_ai-1)*kol+k_ai]->text()=="x") //pion gora
    {
        while(but[(w_ai+temp_wier)*kol+k_ai]->text()=="x")
            temp_wier--;
        //if(but[(w_ai+temp_wier)*kol+k_ai]->text()=="o" && but[(w_ai+1)*kol+k_ai]->text()=="o") return 7;
        if(but[(w_ai+temp_wier)*kol+k_ai]->text()=="o")
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
    else if(but[w_ai*kol+k_ai]->text()=="x" && but[(w_ai+1)*kol+k_ai]->text()=="x") //pion dol
    {
        while(but[(w_ai+temp_wier)*kol+k_ai]->text()=="x")
            temp_wier++;
        //if(but[(w_ai+temp_wier)*kol+k_ai]->text()=="o" && but[(w_ai-1)*kol+k_ai]->text()=="o") return 7;
        if(but[(w_ai+temp_wier)*kol+k_ai]->text()=="o")
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
    /*else if(but[w_ai*kol+k_ai]->text()=="x" && but[(w_ai-1)*kol+k_ai]->text()=="x") //skos / w doł
    {
        while(but[(w_ai+temp_wier)*kol+k_ai]->text()=="x")
            temp_wier--;
        //if(but[(w_ai+temp_wier)*kol+k_ai]->text()=="o" && but[(w_ai+1)*kol+k_ai]->text()=="o") return 7;
        if(but[(w_ai+temp_wier)*kol+k_ai]->text()=="o")
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
    else if(but[w_ai*kol+k_ai]->text()=="x" && but[(w_ai+1)*kol+k_ai]->text()=="x") //skos / w gore
    {
        while(but[(w_ai+temp_wier)*kol+k_ai]->text()=="x")
            temp_wier++;
        //if(but[(w_ai+temp_wier)*kol+k_ai]->text()=="o" && but[(w_ai-1)*kol+k_ai]->text()=="o") return 7;
        if(but[(w_ai+temp_wier)*kol+k_ai]->text()=="o")
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
    }*/
    else return 7;
}

void AI::markButtons(QPushButton **buttons,const int kol,const int wr,int i,int j,QString znak)
{
    buttons[(w_ai+i)*kol+k_ai+j]->setText(znak);
    buttons[(w_ai+i)*kol+k_ai+j]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    buttons[(w_ai+i)*kol+k_ai+j]->setDisabled(1);
}

void AI::markButtons2(QPushButton **buttons,const int kol,const int wr,int i,int j,QString znak)
{
    if(buttons[(wr+i)*kol+j]->text()=="")
    {
    buttons[i*kol+j]->setText(znak);
    buttons[i*kol+j]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
    buttons[i*kol+j]->setDisabled(1);
}
}

int AI::block(QPushButton **buttons, const int kol, const int wr, QString z)
{
   /* int zab=0;
    for(int i=0;i<wr;i++)
    {
        tmp=0;
        for(int j=0;j<kol;j++)
        {
            if(i<=wr/2)
            {
                if( buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol]->text()==z && buttons[j + (i+2) * kol]->text()==z) //pion gora
                    if(zab==0)
                    {
                        if(buttons[j + (i+3) * kol]->text()=="")
                        {
                            markButtons2(buttons,kol,wr,i+4,j,z);
                            return 1;
                        }
                        else if(i-2>=0 && buttons[j + (i-1) * kol]->text()=="")
                        {
                            markButtons2(buttons,kol,wr,i-2,j,z);
                            return 1;
                        }


                    }
                //skosy górna cześć
                if(j + (i+2) * kol-2>=(i+2)*kol && j + (i+2) * kol-2<(i+3)*kol) // skos 1 wariant
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol-1]->text()==z && buttons[j + (i+2) * kol-2]->text()==z)
                        if(zab==0)
                        {

                        }
                }
                if(j + (i+2) * kol+2<(i+3)*kol && j + (i+2) * kol+2>=(i+2)*kol) // skos 2 wariant
                {
                    if(buttons[j + i * kol]->text()==z && buttons[j + (i+1) * kol+1]->text()==z && buttons[j + (i+2) * kol+2]->text()==z)
                        if(zab==0)
                        {

                        }
                }
            }
            else if(i>=wr/2)
            {
                if(buttons[j + i * kol]->text()==z && buttons[j + (i-1) * kol]->text()==z && buttons[j + (i-2) * kol]->text()==z) //pion dół
                    if(zab==0)
                    {
                        if(buttons[j + (i-3) * kol]->text()=="")
                        {
                            markButtons2(buttons,kol,wr,i-4,j,z);
                            return 1;
                        }
                        else if(i+2<=wr && buttons[j + (i+1) * kol]->text()=="")
                        {
                            markButtons2(buttons,kol,wr,i+2,j,z);
                            return 1;
                        }
                    }
                //skosy dolna część
                if(j + (i-2) * kol-2>=(i-2)*kol && j + (i-2) * kol-2<(i-3)*kol) //skos 1 wariant
                {
                    if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z)
                        if(zab==0)
                        {

                        }
                }
                if((j + (i-2) * kol)-2>=(i-2)*kol && (j + (i-2) * kol)-2<(i-3)*kol) //skos 2 wariant
                {
                    if(buttons[j + i * kol]->text()==z && buttons[(j + (i-1) * kol)-1]->text()==z && buttons[(j + (i-2) * kol)-2]->text()==z)
                        if(zab==0)
                        {

                        }
                }
            }
            if(j<=kol/2)
                if(buttons[j + i * kol]->text()==z && buttons[j + i * kol+1]->text()==z && buttons[j + i * kol+2]->text()==z) //poziom lewy
                    if(zab==0)
                    {

                    }
                    else if(j>kol/2)
                        if(buttons[j + i * kol]->text()==z && buttons[j + i * kol-1]->text()==z && buttons[j + i * kol-2]->text()==z) //poziom prawy
                            if(zab==0)
                            {

                            }
        }
    }*/
    return 0;
}
