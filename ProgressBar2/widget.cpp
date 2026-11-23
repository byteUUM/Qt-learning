#include "widget.h"
#include "ui_widget.h"
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->progressBar->setValue(0);
    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        int val = ui->progressBar->value();
        if(val>=100)
        {
            timer->stop();
            return;
        }
        ui->progressBar->setValue(val+5);
        //设置不同的定时器触发时间，模拟网络抖动
        timer->setInterval(10+rand()%500);
    });
    timer->start(500);
}

Widget::~Widget()
{
    delete ui;
}
