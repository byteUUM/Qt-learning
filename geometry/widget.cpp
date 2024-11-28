#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_up_clicked()
{
    QRect rect=ui->pushButton->geometry();
//    rect.setY(rect.y()-5);
//    ui->pushButton->setGeometry(rect);
    ui->pushButton->setGeometry(rect.x(),rect.y()-5,rect.width(),rect.height());
}

void Widget::on_left_clicked()
{
    QRect rect=ui->pushButton->geometry();
//    rect.setX(rect.x()-5);
//    ui->pushButton->setGeometry(rect);
    ui->pushButton->setGeometry(rect.x()-5,rect.y(),rect.width(),rect.height());
}

void Widget::on_right_clicked()
{
    QRect rect=ui->pushButton->geometry();
//    rect.setX(rect.x()+5);
//    ui->pushButton->setGeometry(rect);
    ui->pushButton->setGeometry(rect.x()+5,rect.y(),rect.width(),rect.height());
}

void Widget::on_down_clicked()
{
    QRect rect=ui->pushButton->geometry();
//    rect.setY(rect.y()+5);
//    ui->pushButton->setGeometry(rect);
    ui->pushButton->setGeometry(rect.x(),rect.y()+5,rect.width(),rect.height());
}
