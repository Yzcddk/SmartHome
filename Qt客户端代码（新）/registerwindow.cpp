#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QMainWindow>
#include<QDebug>
#include<QChar>
#include<QMessageBox>
#include<tcpsocket.h>
#include"severaddress.h"
#include"userinformation.h"


RegisterWindow::RegisterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    TcpSocket *tcpsocket=new  TcpSocket;
    connect(this,SIGNAL(addressSet(UserInformation)),tcpsocket,SLOT(TcpSeverset(UserInformation)));
     connect(tcpsocket,SIGNAL(registerStatu(QString)),this,SLOT(showRegisterResult(QString)));
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

bool RegisterWindow::checkEmail(const QString &email)
{
    //asdfsdfsdf@163/qq/gmail.com
   bool ok=email.contains("@") && email.contains(".com");
   if(!ok){
       return false;
   }
   QString str1= email.section('@',0,0);
   if(str1.isEmpty())
   {
       return false;
   }
    QString str2= email.section('@',1,1);
    if(str1==".com")
    {
        return false;
    }
    return true;
}

bool RegisterWindow::checkphone(const QString &phone)
{
 if(phone.length()!=11)
 {
     return false;
 }
 for(int i=0;i<phone.length();i++){
     QChar num=phone.at(i);
     if(num>='0'&&num<='9'){
         continue;
     }else{
         return false;
     }
 }return true;
}



void RegisterWindow::on_commitButton_clicked()
{

  QString errostring;
  QString username=ui->username->text();
  if(username.isEmpty()){
      errostring+="1.用户名不能为空\n";
  }

  QString password=ui->password->text();
  if(password.isEmpty()){
      errostring+="1.密码不能为空\n";
  }


QString email=ui->email->text();
 bool ok=checkEmail(email);
if(!ok)
{
   errostring+="3.邮箱格式错误\n";
}

QString phone=ui->phone->text();
ok=checkphone(phone);
      if(!ok)
        {
          errostring+="4.手机号码格式错误\n";
        }
      if(!errostring.isEmpty()){
         // qDebug()<<errostring;
          QMessageBox::warning(NULL,"输入的信息错误",errostring,QMessageBox::Yes,QMessageBox::Yes);
          return;
      }
       UserInformation user(username,password,email,phone);
      emit addressSet(user);

}

void  RegisterWindow::RegisterWindowshow(){
   /*ui->password->clear();
    ui->username->clear();
    ui->email->clear();
    ui->phone->clear();*/

    show();
}
void RegisterWindow::showRegisterResult(const QString &error)
{
    if(error.isEmpty()){
        QMessageBox::information(NULL,"注册用户","祝贺您，注册成功",QMessageBox::Yes,QMessageBox::Yes);
    }else{
        QString str = QString("很遗憾，注册失败:%1").arg(error);
        QMessageBox::warning(NULL,"注册用户",str,QMessageBox::Yes,QMessageBox::Yes);
    }
}
