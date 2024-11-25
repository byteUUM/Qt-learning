#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QLabel* lb=new QLabel(this);
    lb->setText("hello world");
}

Widget::~Widget()
{
    delete ui;
}

