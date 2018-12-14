#include "resultwindow.h"
#include "ui_resultwindow.h"

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
    {
        ui->lose->setText("WYGRAŁEŚ");
    }else {ui->lose->setText("PRZEGRAŁEŚ");}

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