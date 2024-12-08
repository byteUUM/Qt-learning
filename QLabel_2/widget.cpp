#include "widget.h"
#include "ui_widget.h"
#include <QResizeEvent>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QRect p=this->geometry();
    ui->label->setGeometry(0,0,p.width(),p.height());

    QPixmap px(":/demon.png");
    ui->label->setPixmap(px);

    ui->label->setScaledContents(true);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event)
{
       qDebug()<<event->size();
       ui->label->setGeometry(0,0,event->size().width(),event->size().height());
}
