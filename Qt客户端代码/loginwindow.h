#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "registerwindow.h"
#include "serveraddressdialog.h"


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

signals:
    void showRegisterWindow(void);

private slots:
    void on_checkButton_clicked(bool checked);
    void on_registerAction_triggered();

    void on_serverAction_triggered();

private:
    Ui::LoginWindow *ui;
    RegisterWindow *regWin;
    ServerAddressDialog *addressDialog;
};

#endif // LOGINWINDOW_H
