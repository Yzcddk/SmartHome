#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerwindow.h"
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    regWin = new RegisterWindow;
    connect(this,SIGNAL(showRegisterWindow()),regWin,SLOT(registerWindowShow()));

    addressDialog = new ServerAddressDialog;
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete regWin;
}

void LoginWindow::on_checkButton_clicked(bool checked)
{
    qDebug() << checked;
    if(checked  == true){
        ui->checkButton->setText("√");
    }else{
        ui->checkButton->setText("");
    }
}

void LoginWindow::on_registerAction_triggered()
{
    qDebug() << "register action";
    emit showRegisterWindow();
}

void LoginWindow::on_serverAction_triggered()
{
    addressDialog->show();
}
