#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>

namespace Ui {
class ResultWindow;
}

class ResultWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResultWindow(QWidget *parent = nullptr);
    ~ResultWindow();
    void wybor(QString z="");
    int wynik{};
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ResultWindow *ui;
};

#endif // RESULTWINDOW_H
