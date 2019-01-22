#ifndef TTTMAINWINDOW_H
#define TTTMAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
namespace Ui {
class TTTmainWindow;
}

class TTTmainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TTTmainWindow(QWidget *parent = nullptr);
    ~TTTmainWindow();
    QString znak1="o",znak2="x";
    int wiersze{},kolumny{};
    int tryb{};
    int wiel_przyciskow{};
    bool cofnij{};
    QString zaczyna="o";
private slots:

        void on_Zakoncz_clicked();

        void on_Start_clicked();

        void on_buttonBox_accepted();

        void on_buttonBox_rejected();

        void on_Znak_activated(const QString &arg1);

        void on_Tryb_activated(const QString &arg1);

        void on_comboBox_activated(const QString &arg1);

        void on_comboBox_2_activated(const QString &arg1);

        void on_spinBox_valueChanged();

private:
    int max_wr{},max_kol{};
    int x{},y{};
    Ui::TTTmainWindow *ui;
};

#endif // TTTMAINWINDOW_H
