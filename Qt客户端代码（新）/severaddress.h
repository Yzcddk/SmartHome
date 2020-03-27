#ifndef SEVERADDRESS_H
#define SEVERADDRESS_H

#include <QDialog>

namespace Ui {
class severwindow;
}

class severwindow : public QDialog
{
    Q_OBJECT

public:
    explicit severwindow(QWidget *parent = 0);
    ~severwindow();

void closeEvent(QCloseEvent *event);




static QString getServerIp();
static void setServerIp(const QString &value);

static short getServerPort();
static void setServerPort(short value);

public  slots:

void addressWindowshow();


private:
Ui::severAddress *ui;
static QString serverIp;
    static short serverPort;

};

#endif // SEVERADDRESS_H
