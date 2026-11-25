#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->dial->setValue(100);//初始值
    ui->dial->setMaximum(100);//最大值
    ui->dial->setMinimum(1);//最小值

    ui->dial->setNotchesVisible(true);//显示刻度
}


Widget::~Widget()
{
    delete ui;
}

void Widget::on_dial_valueChanged(int value)
{
    this->setWindowOpacity(value/100.0);
}

