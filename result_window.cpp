#include "result_window.h"
#include "ui_realoadgame.h"
#include "tttmainwindow.h"

Realoadgame::Realoadgame(QWidget *parent,QString z) :
    QDialog(parent),
    ui(new Ui::Realoadgame)
{
    ui->setupUi(this);
    if(z=="o")
    {

    }

}

Realoadgame::~Realoadgame()
{
    delete ui;
}

void Realoadgame::on_pushButton_clicked()
{
    TTTmainWindow t;
    t.show();
}
