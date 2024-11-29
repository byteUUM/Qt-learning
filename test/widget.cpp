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


void Widget::on_pushButton_2_clicked()
{
//    int width=this->geometry().width();
//    int height=this->geometry().height();
//    ui->pushButton_2->move(rand()%(width-20),rand()%(height-20));
}

void Widget::on_pushButton_clicked()
{
    ui->label_3->setText("谢谢导员，我们就知道导员最好了，一定会批准的");
    ui->pushButton_2->setEnabled(false);
}

void Widget::on_pushButton_2_pressed()
{
    int width=this->geometry().width();
    int height=this->geometry().height();
    ui->pushButton_2->move(rand()%(width-20),rand()%(height-20));
}
