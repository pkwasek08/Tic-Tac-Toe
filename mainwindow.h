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

    QPushButton *buttons[30][30]{},butt{};
    QObject* button = QObject::sender();
    QGridLayout *view=new QGridLayout();
    int wr{},kol{};
    void Plansza();
    void AI();

private:
    Ui::MainWindow *ui;
    int w_r{},k_r{};
    int max_w{};
    int max_k{};

private slots:
    void Klik(); //ruch gracza



};

#endif // MAINWINDOW_H