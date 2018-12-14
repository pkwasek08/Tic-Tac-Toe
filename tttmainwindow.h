#ifndef TTTMAINWINDOW_H
#define TTTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class TTTmainWindow;
}

class TTTmainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TTTmainWindow(QWidget *parent = nullptr);
    ~TTTmainWindow();
    QString wiersze,kolumny;
private slots:

        void on_Zakoncz_clicked();

        void on_Start_clicked();

        void on_buttonBox_accepted();

        void on_buttonBox_rejected();

private:
    Ui::TTTmainWindow *ui;
};

#endif // TTTMAINWINDOW_H
