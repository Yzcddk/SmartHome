#include "severaction.h"
#include "ui_severaction.h"

severAction::severAction(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::severAction)
{
    ui->setupUi(this);
}

severAction::~severAction()
{
    delete ui;
}
