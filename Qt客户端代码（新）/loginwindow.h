#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include<QChar>
#include "registerwindow.h"
#include "severaddress.h"
#include<QTcpSocket>
#include"mainwindow.h"
#include"tcpsocket.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();



  //  bool checkpassword(const QString &password);
   // bool checkusername(const QString &username);
   void savaLoginUser(QString &username,QString &password);
   void display(void);

signals:
    void showRegisterWindow(void);
    void showseverWindow(void);
    void userReady(const  UserInformation &user);
    void loginUser(const QString &username,const QString &password);
private slots:
    void on_checkButton_clicked(bool checked);
    void on_registerAction_triggered();

    void on_severAction_triggered();



    void on_pushButton_2_clicked();
    void resultReturn(const QString &error,const QString &clientId);

private:
    Ui::LoginWindow *ui;
    RegisterWindow *regWin;
    severAddress *severWin;
     TcpSocket *tcp;



    QString username;
    QString password;

};

#endif // LOGINWINDOW_H
