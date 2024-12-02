#include "widget.h"
#include "ui_widget.h"
#include <QString>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label_2->setStyleSheet(QString("font:楷体;color:green;"));

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    this->setStyleSheet(QString("background-color:rgb(240,240,240);color:black;"));
}

void Widget::on_pushButton_2_clicked()
{
    this->setStyleSheet(QString("background-color:back;color:white;"));
}
