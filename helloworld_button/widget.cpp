#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::handleClick);
    button = new QPushButton(this);
    button->setText("hello world");
    button->move(200,300);
    this->move(0,0);
    connect(button,&QPushButton::clicked,this,&Widget::handleClick2);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::handleClick()
{
    if(ui->pushButton->text()=="hello world")
        ui->pushButton->setText("hello qt");
    else
        ui->pushButton->setText("hello world");
}

void Widget::handleClick2()
{
    if(button->text()=="hello world")
        button->setText("hello qt");
    else
        button->setText("hello world");
}
