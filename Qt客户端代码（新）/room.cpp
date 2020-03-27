#include "room.h"
#include "ui_room.h"
#include<QDebug>

room::room(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::room)
{
    ui->setupUi(this);
}

room::~room()
{
    delete ui;
}

void room::on_led1button_clicked(bool checked)
{
    int statu;
    if(checked){
        ui->led1button->setStyleSheet("border-image: url(:/image/login/OFF.png)");
        ui->led1->setStyleSheet("border-image: url(:/image/login/closeled_ico.png)");
        statu=0;//打开
    }else{
        ui->led1button->setStyleSheet("border-image: url(:/image/login/ON.png)");
        ui->led1->setStyleSheet("border-image: url(:/image/login/openled_ico.png)");
        statu=1;
    }
    emit controlDevice(1,statu);
}

void room::on_ledbutton2_clicked(bool checked){
      int statu;
    if(checked)
    {

        ui->ledbutton2->setStyleSheet("border-image: url(:/image/login/OFF.png)");
         ui->led2->setStyleSheet("border-image: url(:/image/login/closeled_ico.png)");
         statu=0;
    }else
    {
            ui->ledbutton2->setStyleSheet("border-image: url(:/image/login/ON.png)");
            ui->led2->setStyleSheet("border-image: url(:/image/login/openled_ico.png)");
            statu=1;
    }
    emit controlDevice(2,statu);
    }


void room::on_fengbutton_clicked(bool checked)
{
    int statu;
    if(checked){
        ui->feng->setStyleSheet("border-image: url(:/image/login/closefan_ico.png);");
        ui->fengbutton->setStyleSheet("border-image: url(:/image/login/OFF.png)");
           statu = 0;
    }else{
        ui->feng->setStyleSheet("border-image: url(:/image/login/openfan_ico.png);");
        ui->fengbutton->setStyleSheet("border-image: url(:/image/login/ON.png)");
           statu = 1;
    }
        emit controlDevice(3,statu);
}

void room::on_doorbutton_clicked(bool checked)
{
        int statu;
    if(checked){
        ui->door->setStyleSheet("border-image: url(:/image/login/closedoor_ico.png);");
        ui->doorbutton->setStyleSheet("border-image: url(:/image/login/OFF.png)");
               statu = 0;
    }else{
        ui->door->setStyleSheet("border-image: url(:/image/login/opendoor_ico.png);");
        ui->doorbutton->setStyleSheet("border-image: url(:/image/login/ON.png)");
                statu = 1;
    }
        emit controlDevice(4,statu);
}
