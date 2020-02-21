#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "tcpsocket.h"
#include <QDebug>
#include <QMessageBox>

RegisterWindow::RegisterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);

    TcpSocket *tcpSocket = new TcpSocket;
    connect(this,SIGNAL(registerUserReady()),tcpSocket,SLOT(registerUserByTcp()));
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

bool RegisterWindow::checkEmail(const QString &email)
{
    //@.com
    //asdsafd@163/qq/gmail.com
    bool ok = email.contains("@") && email.endsWith(".com");
    if(!ok){
        return false;
    }

    QString str1 = email.section('@',0,0);
    if(str1.isEmpty()){
        return false;
    }

    QString str2 = email.section('@',1,1);
    if(str2 == ".com"){
        return false;
    }

    return true;
}

bool RegisterWindow::checkTelPhone(const QString &phone)
{
    //都是数字，并且是11位
    if(phone.length() != 11){
        return false;
    }

    for(int i = 0;i < phone.size();i ++){
        QChar ch = phone.at(i);
        if(ch >= '0' && ch <= '9'){
            continue;
        }else{
            return false;
        }
    }

    return true;
}

void RegisterWindow::on_commitButton_clicked()
{
    QString errorString;

    QString username = ui->username->text();
    if(username.isEmpty()){
        errorString += "1.用户名不能为空\n";
    }

    QString password = ui->password->text();
    if(password.isEmpty()){
        errorString += "2.密码不能为空\n";
    }

    QString email = ui->email->text();
    bool ok = checkEmail(email);
    if(!ok){
        errorString += "3.邮箱格式错误，请输入正确的邮箱\n";
    }

    QString telPhone = ui->phone->text();
    ok = checkTelPhone(telPhone);
    if(!ok){
         errorString += "4.电话号码格式错误，请输入正确的电话号码\n";
     }

    if(!errorString.isEmpty()){
        //qDebug() << errorString;
        QMessageBox::warning(NULL,"输入的信息错误",errorString,QMessageBox::Yes,QMessageBox::Yes);
        return;
    }

    emit registerUserReady();
}

void RegisterWindow::registerWindowShow()
{
    ui->username->clear();
    ui->password->clear();
    ui->email->clear();
    ui->phone->clear();

    this->show();
}
