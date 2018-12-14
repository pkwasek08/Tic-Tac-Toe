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
    void sprawdz(QString z="");
    void koniec(QString z="");
    void Plansza(QString wr_ustawione, QString kol_ustawione);
    void AI();
    int random(int nMin, int nMax);

    QPushButton **buttons;
    const QSize btnSize = QSize(60, 60);
    QObject* button = QObject::sender();
     //auto gridLayout = new QGridLayout(&mainWindow);
    QVBoxLayout *view=new QVBoxLayout();
    QWidget w;
    int tmp_restart{};
    int tmp;
    int wr{},kol{};
    int w_r{},k_r{};

private:

    int max_w{};
    int max_k{};

private slots:
    void Klik(); //ruch gracza


private:
    Ui::Game *ui;
};

#endif // GAME_H
