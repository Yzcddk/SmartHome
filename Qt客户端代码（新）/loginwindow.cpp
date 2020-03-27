#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerwindow.h"
#include"tcpsocket.h"
#include<QDebug>
#include<QHostAddress>
#include"userinformation.h"
#include<QMessageBox>
#include<QFile>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    regWin = new RegisterWindow;
    severWin=new severAddress;



    tcp=new TcpSocket;
    connect(this,SIGNAL(loginUser(QString,QString)),tcp,SLOT(loginUserByTcp(QString,QString)));
    connect(this,SIGNAL(showRegisterWindow()),regWin,SLOT(RegisterWindowshow()));
    connect(this,SIGNAL(showseverWindow()),severWin,SLOT(addressWindowshow()));
    connect(this,SIGNAL(userReady(UserInformation)),tcp,SLOT(TcpSeverset(UserInformation)));
    //connect(tcp,SIGNAL(loginSuccess(QString)),this,SLOT(resultReturn(QString)));
    connect(tcp,SIGNAL(loginStatu(QString,QString)),this,SLOT(resultReturn(QString,QString)));

    bool ok=QFile::exists("user.txt");
    if(ok){
        display();
        ui->checkButton->setText("√");
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete regWin;
    delete tcp;
    delete severWin;
}

void LoginWindow::savaLoginUser(QString &username, QString &password)
{
    QFile file("user.txt");
    bool ok = file.open(QFile::WriteOnly);
    if(!ok){
        qDebug() << "Fail to open user.txt : " << file.errorString();
        return;
    }

    username += "\n";
    password += "\n";
    file.write(username.toUtf8());
    file.write(password.toUtf8());

    file.close();

    return;
}

void LoginWindow::display()
{
    QFile file("user.txt");
    bool ok = file.open(QFile::ReadOnly);
    if(!ok){
        qDebug() << "Fail to open user.txt : " << file.errorString();
        return;
    }

    QString username = file.readLine();
    username.remove("\n");
    QString password = file.readLine();
    password.remove("\n");
    ui->lineEdit->setText(username);
    ui->lineEdit_2->setText(password);

    file.close();
    return;
}

void LoginWindow::on_checkButton_clicked(bool checked)
{
    if(checked==true)
    {
        ui->checkButton->setText("√");
        QString username = ui->lineEdit->text();
                QString password = ui->lineEdit_2->text();
                     savaLoginUser(username,password);
    }else{
        ui->checkButton->setText("");
             QFile::remove("user.txt");
    }
}


void LoginWindow::on_registerAction_triggered()
{
    qDebug() << "register action1";
    emit showRegisterWindow();
}

void LoginWindow::on_severAction_triggered()
{

 emit showseverWindow();
}

void LoginWindow::on_pushButton_2_clicked()//点击登陆按钮
{
QString username=ui->lineEdit->text();//获取账户信息
QString error;
if(username.isEmpty()){
    error+="账号不能为空\n";
}
QString password=ui->lineEdit_2->text();//获取密码信息
if(password.isEmpty())
{
    error+="密码不能为空";
}
#if 1
if(!error.isEmpty()){
    QMessageBox::warning(NULL,"输入的信息错误",error,QMessageBox::Yes,QMessageBox::Yes);//若输入信息有误，则报错
}else{
    emit loginUser(username,password);//若输入信息无错误，发送信号loginuser(),同时调用槽函数loginUserByTcp().
}
#endif
//resultReturn("","1234");
}

void LoginWindow::resultReturn(const QString &error, const QString &clientId)
{
    if(!error.isEmpty()){
        QString str = QString("很遗憾，登陆失败").arg(error);
        QMessageBox::warning(NULL,"登陆失败",str,QMessageBox::Yes,QMessageBox::Yes);
        return;

    }else{


        //QString str = QString("登陆成功").arg(error);
        //QMessageBox::warning(NULL,"",str,QMessageBox::Yes,QMessageBox::Yes);

        MainWindow *mainWin=new MainWindow;
       mainWin->setClienId(clientId);
       //this->close();
        mainWin->show();

      qDebug()<<"clientId:"<<clientId;

    }



}

