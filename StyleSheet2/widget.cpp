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

void Widget::on_pushButton_clicked()
{
    this->setStyleSheet("background-color: rgb(243,243,243);");
    ui->plainTextEdit->setStyleSheet("background-color:white;color:black;");
    ui->pushButton->setStyleSheet("color:black;");
    ui->pushButton_2->setStyleSheet("color:black;");
}

void Widget::on_pushButton_2_clicked()
{
    this->setStyleSheet("background-color: black;");
    ui->plainTextEdit->setStyleSheet("background-color:black;color:white;");
    ui->pushButton->setStyleSheet("color:white;");
    ui->pushButton_2->setStyleSheet("color:white;");
}

