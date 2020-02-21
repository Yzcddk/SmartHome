#include "serveraddressdialog.h"
#include "ui_serveraddressdialog.h"
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>
#include <QCloseEvent>

QString ServerAddressDialog::serverIP;
short ServerAddressDialog::serverPort;

ServerAddressDialog::ServerAddressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerAddressDialog)
{
    ui->setupUi(this);
}

ServerAddressDialog::~ServerAddressDialog()
{
    delete ui;
}

void ServerAddressDialog::closeEvent(QCloseEvent *event)
{
    QString errorString;
    QString ip = ui->ipLineEdit->text();
    QHostAddress ipAddress(ip);
    if(ip.isEmpty() || ipAddress.isNull()){
        errorString += "1.请输入正确的服务器端IP\n";
    }

    QString port = ui->portLineEdit->text();
    bool ok;
    port.toShort(&ok);
    if(port.isEmpty() || !ok){
        errorString +="2.请输入正确的服务器端Port\n";
    }

    if(!errorString.isEmpty()){
        int ret = QMessageBox::warning(NULL,"输入的服务器端地址信息错误",errorString,QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(ret == QMessageBox::Yes){
           event->ignore();//忽略关闭事件
        }
        return;
    }

    serverIP   = ip;
    serverPort = port.toShort(&ok);

    return;
}

QString ServerAddressDialog::getServerIP()
{
    return serverIP;
}

void ServerAddressDialog::setServerIP(const QString &value)
{
    serverIP = value;
}

short ServerAddressDialog::getServerPort()
{
    return serverPort;
}

void ServerAddressDialog::setServerPort(short value)
{
    serverPort = value;
}
