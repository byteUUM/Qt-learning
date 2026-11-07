#include "widget.h"
#include "ui_widget.h"
#include <QLabel>
#include "mylabel.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //QLabel* hw = new QLabel(this);
    //hw->setText("hello world");
    MyLabel* hw = new MyLabel(this);
    hw->setText("hello world");
}

Widget::~Widget()
{
    delete ui;
}
