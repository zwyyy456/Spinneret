#ifndef SECOND_H
#define SECOND_H

#include <QWidget>

namespace Ui {
class second;
}

class second : public QWidget
{
    Q_OBJECT

public:
    explicit second(QWidget *parent = nullptr);
    Ui::second *ui;
    ~second();

private:

};

#endif // SECOND_H
