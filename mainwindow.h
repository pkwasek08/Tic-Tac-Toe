#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "start.h"
#include "game.h"
#include <QPixmap>
#include <QtWidgets>


namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class rules;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPushButton *buttons[30][30]{};
    QObject* button = QObject::sender();
    QGridLayout *view=new QGridLayout();
public:
    int wr,kol;

    void Plansza();

private slots:

private:
    Ui::MainWindow *ui;

    int w_r,k_r;

private slots:
    void Klik(); //ruch gracza



};

#endif // MAINWINDOW_H
