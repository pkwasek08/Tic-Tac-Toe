#ifndef GAME_H
#define GAME_H

#pragma GCC diagnostic ignored "-Wdangling-else"
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
    void sprawdz(QString z="");
    void koniec(QString z="");
    void Plansza(int wr_ustawione, int kol_ustawione,QString znak_1gracza,QString znak_2gracza,int tryb_gry); //int tryb
    int gracz{};
    int tryb{};
    QPushButton **buttons;
    const QSize btnSize = QSize(60, 60);
    QObject* button = QObject::sender();
    QVBoxLayout *view=new QVBoxLayout();
    QWidget w;
    int tmp,tmp2{};
    int wr{},kol{};
    int w_r{},k_r{};
    QString gracz1,gracz2;
    int tmp_restart{};

private:

private slots:
    void Klik(); //ruch gracza

private:
    Ui::Game *ui;
};

#endif // GAME_H
