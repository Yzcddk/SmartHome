#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>
#include"userinformation.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = 0);
    ~RegisterWindow();
    bool checkEmail(const QString &email);
    bool checkphone(const QString &phone);
    //bool checkpassword(const QString &password);
   signals:
    void addressSet(const UserInformation &user);

private slots:
    void on_commitButton_clicked();
    void RegisterWindowshow();
void showRegisterResult(const QString &error);
private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOW_H
