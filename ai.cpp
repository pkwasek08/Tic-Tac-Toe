#include "ai.h"

AI::AI()
{

}

void AI::choosebutton(QPushButton **buttons,const int kol,const int wr,QString znak)
{
    int w_ai{},k_ai{};
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
    }else
    {
        do
         {
         if(w_r==0 || k_r==0) {w_r=1; k_r=1;}
         if(w_r==wr || k_r==kol) {w_r=wr-1; k_r=kol-1;}
        w_ai=random(w_r-1,w_r+1);
        k_ai=random(k_r-1,k_r+1);
          }
         while(w_ai<0 || k_ai<0 || w_ai>wr || k_ai>kol ||
           buttons[w_ai*kol+k_ai]->text()=="o" || buttons[w_ai*kol+k_ai]->text()=="x");
        // Sleep(1000);
        buttons[w_ai*kol+k_ai]->setText(znak);
        buttons[w_ai*kol+k_ai]->setStyleSheet("QPushButton{font-size: 30px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);}");
        buttons[w_ai*kol+k_ai]->setDisabled(1);
        w_r=w_ai;
        k_r=k_ai;
    }
}


int AI::random(int nMin, int nMax)
{
    srand(time(0));
    return rand() % (nMax - nMin + 1 ) + nMin;
}
