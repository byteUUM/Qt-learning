#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPushButton* button=new QPushButton(this);
    connect(button,&QPushButton::clicked,this,[=](){button->setText("begin");});
}

Widget::~Widget()
{
    delete ui;
}
void Widget::on_pushButton_clicked()
{
    if(ui->pushButton->text()==QString("begin"))
        ui->pushButton->setText("end");
    else ui->pushButton->setText("begin");
}

void Widget::on_pushButton_2_clicked()
{
    disconnect(ui->pushButton,&QPushButton::clicked,this,&Widget::on_pushButton_clicked);
    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::newPushButton);
    ui->pushButton_2->setText("success");
}

void Widget::newPushButton()
{
    ui->pushButton->setText("hello qt");
}
