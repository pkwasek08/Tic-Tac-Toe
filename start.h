#ifndef START_H
#define START_H

#include <QDialog>

namespace Ui {
class start;
}

class start : public QDialog
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = nullptr);
    ~start();
    QString wiersze{},kolunmy{};
    void create_game();
    void wygrana();
        void przegrana();
        int rest{};
private slots:
    void on_buttonBox_accepted();

    void on_start_rejected();

private:
    Ui::start *ui;
};

#endif // START_H
