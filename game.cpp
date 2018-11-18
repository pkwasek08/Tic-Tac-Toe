#include "game.h"


game::game(int wr,int kol)
{

}

int game::rand_wr(int wr)
{
    return rand()%wr;
}

int game::rand_kol(int kol)
{
    return rand()%kol;
}
//void game::sprawdz()
//{
//    MainWindow m;

//    for(int i=0;i<m.wr;i++)
//    {
//        for(int j=0;j<m.kol;j++)
//        {

//            if(m.buttons[i][j]->text()=="o" && m.buttons[i-m.wr][j]->text()=="o" && m.buttons[i+m.wr][j]->text()=="o")
//            {
//                QMessageBox msgBox;
//                msgBox.setWindowTitle("WYGRANA");
//                msgBox.setText("WYGRAŁEŚ");
//                msgBox.setStandardButtons(QMessageBox::Ok);
//                msgBox.setDefaultButton(QMessageBox::Ok);
//            }
//        }
//    }
//}
void game::AI()
{

}
