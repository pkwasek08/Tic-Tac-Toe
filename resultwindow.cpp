#include "resultwindow.h"
#include "ui_resultwindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

ResultWindow::ResultWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultWindow)
{
    ui->setupUi(this);
}

ResultWindow::~ResultWindow()
{
    delete ui;
}
void ResultWindow::wybor(QString z)
{
    if(z=="o")
        ui->lose->setText("WYGRAŁO KÓŁKO");
    else if(z=="x")
        ui->lose->setText("WYGRAŁ KRZYŻYK");
    else ui->lose->setText("REMIS");

    ui->lose->setAlignment(Qt::AlignCenter);
    ui->label->setAlignment(Qt::AlignCenter);

    exec();
}
void ResultWindow::on_pushButton_clicked()
{
    wynik=1;
    close();
}

void ResultWindow::on_pushButton_2_clicked()
{
    wynik=-1;
    close();
}
