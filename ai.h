#ifndef AI_H
#define AI_H

#include <QtWidgets>
#include <QTime>

class AI
{
public:
    AI();

    void choosebutton(QPushButton **buttons,const int kol,const int wr,QString gracz,QString znak_ai);
    int cofnij_proby{};
    void setColor(QString color);
    int test(QPushButton **buttons, const int kol, const int wr);
    int tmp{};
    int cofnij_w_ai{},cofnij_k_ai{};

private:
   int w_r{},k_r{};
    int w_ai{},k_ai{};
    int random(int nMin, int nMax);
    int markButtons(QPushButton **buttons,const int kol,int i,int j,QString znak);
    int direction_2(QPushButton **buttons,const int kol,const int wr,QString znak_ai);
    int block(QPushButton **buttons,const int kol,const int wr,QString znak,QString znak_ai);
    int win(QPushButton **buttons,const int kol,const int wr,QString znak,QString z_ai);
    void markButtons2(QPushButton **buttons,const int kol,int i,int j,QString znak);
    int specialCase(QPushButton **buttons, const int kol, const int wr, QString z ,QString znak_ai);
    QString paint{};

};

#endif // AI_H
