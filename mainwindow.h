#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "start.h"
#include <QPixmap>
#include <QtWidgets>
#include <QApplication>
#include <QWidget>
#include <QGridLayout>



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

    QPushButton **buttons;
    const QSize btnSize = QSize(60, 60);
    QObject* button = QObject::sender();
     //auto gridLayout = new QGridLayout(&mainWindow);
    QVBoxLayout *view=new QVBoxLayout();
    QWidget w;
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
