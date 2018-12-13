#ifndef WYBOR_H
#define WYBOR_H

#include <QWidget>

namespace Ui {
class wybor;
}

class wybor : public QWidget
{
    Q_OBJECT

public:
    explicit wybor(QWidget *parent = nullptr);
    ~wybor();

private:
    Ui::wybor *ui;
};

#endif // WYBOR_H
