#include "widget.h"
#include "ui_widget.h"
#include "QTimer"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lcdNumber->display(10.0);
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Widget::func);
    timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::func()
{
    double num=ui->lcdNumber->value();
    if(num<=0.1)
    {
        ui->lcdNumber->display(0.0);
        timer->stop();
        return;
    }
    if(num==k)
    {
        k/=10;
    }
    ui->lcdNumber->display(num-k);

}

