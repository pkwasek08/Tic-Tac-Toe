#include "rules.h"
#include "mainwindow.h"
#include "start.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QtWidgets>
rules::rules()
{

}

void rules::sprawdz()
{
    MainWindow ma;
    start s;
    for(int i=0;i<wr_r;i++)
    {
        for(int j=0;j<kol_r;j++)
        {

            if(ma.buttons[i][j]->text()=="o" && ma.buttons[i-wr_r][j]->text()=="o" && ma.buttons[i+wr_r][j]->text()=="o")
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("WYGRANA");
                msgBox.setText("WYGRAŁEŚ");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setDefaultButton(QMessageBox::Ok);
            }
    }  }

}
