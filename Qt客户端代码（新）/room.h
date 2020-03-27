#ifndef ROOM_H
#define ROOM_H

#include <QMainWindow>


namespace Ui {
class room;
}

class room : public QMainWindow
{
    Q_OBJECT

public:
    explicit room(QWidget *parent = 0);
    ~room();
signals:
    void controlDevice(int deviceId,int statu);

private slots:
    void on_led1button_clicked(bool checked);

    void on_ledbutton2_clicked(bool checked);

    void on_fengbutton_clicked(bool checked);

    void on_doorbutton_clicked(bool checked);

private:
    Ui::room *ui;
};

#endif // ROOM_H
