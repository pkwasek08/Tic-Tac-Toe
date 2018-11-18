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

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

QPushButton *buttons[30][30];
    QObject* button = QObject::sender();
    QGridLayout *view=new QGridLayout();
public:    int wr,kol;

    void Plansza();
   // int i=0,j=0;
 //   int *tab1 = new int[30];
  //  int *tab2 = new int[30];
private slots:

private:
    Ui::MainWindow *ui;

    int w_r,k_r;

private slots:
    void Klik(); //ruch gracza



};

#endif // MAINWINDOW_H
