#include "severaddress.h"
#include "ui_severaddress.h"
#include<QDebug>
#include<QMessageBox>
#include<QChar>
#include<QHostAddress>
#include<QCloseEvent>
QString severAddress::serverIp ;
short severAddress::serverPort ;

severAddress::severAddress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::severAddress)
{
    ui->setupUi(this);
}

severAddress::~severAddress()
{
    delete ui;
}

void severAddress::addressWindowshow()
{
    /*ui->ip->clear();
    ui->port->clear();*/
    show();
}

short severAddress::getServerPort()
{
    return serverPort;
}

void severAddress::setServerPort(short value)
{
    serverPort = value;
}

QString severAddress::getServerIp()
{
    return serverIp;
}

void severAddress::setServerIp(const QString &value)
{
    serverIp = value;
}



void severAddress::closeEvent(QCloseEvent *event)
{

    QString errostring;
    QString ip =ui->ip->text();
    QHostAddress ipAddress(ip);
      if(ip.isEmpty() || ipAddress.isNull()){
          errostring+="ip地址设置有误\n";
      }


    QString port =ui->port->text();
    bool ok;
    port.toShort(&ok);
if(port.isEmpty()||!ok){
    errostring+="端口信息输入有误\n";
}
if(!errostring.isEmpty()){
     int ret=QMessageBox::warning(NULL,"错误:",errostring,QMessageBox::Yes,QMessageBox::No);
      if(ret==QMessageBox::Yes){
       event->ignore();//忽略关闭事件
    }

     return;
}
serverIp=ip;
serverPort=port.toShort(&ok);
return;
}

