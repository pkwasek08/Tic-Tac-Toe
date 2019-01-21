#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QMainWindow>
#include "tttmainwindow.h"
#include <QPixmap>
#include <QtWidgets>
#include <QApplication>
#include <QWidget>
#include <QGridLayout>

namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    void Plansza(int wr_ustawione, int kol_ustawione,QString znak_1gracza,QString znak_2gracza,int tryb_gry,int wiel_przyciskow,bool cofnij,QString zaczyna); //int tryb

    QPushButton **buttons;
    int wr{},kol{};
    int tmp_restart{};

private slots:
    void Klik(); //ruch gracza
    void Cofnij();

private:
    Ui::Game *ui;
    int tmp,tmp2{};
    int w_r{},k_r{};
    QString gracz1,gracz2;
    int cofnij_tmp{};
    int cofnij_w_gracz{},cofnij_k_gracz{};
    QPushButton *bb{};
    int cofnij1{},cofnij2{};
    bool back{};
    QString paint1,paint2;
    int trybik{};
    QVBoxLayout *view=new QVBoxLayout();
    QWidget w;
    QObject* button = QObject::sender();
    int sprawdz(QString z="");
    void koniec(QString z="");
    int gracz{};
    int tryb{};
    QGridLayout *buttonsLayout{};
    QString paint_cofnij_grey="QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(192,192,192);}";
    QString paint_cofnij_black="QPushButton{font-size: 40px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(0,0,0);}";
};

#endif // GAME_H
