#ifndef SEVERACTION_H
#define SEVERACTION_H

#include <QMainWindow>

namespace Ui {
class severAction;
}

class severAction : public QMainWindow
{
    Q_OBJECT

public:
    explicit severAction(QWidget *parent = 0);
    ~severAction();

private:
    Ui::severAction *ui;
};

#endif // SEVERACTION_H
