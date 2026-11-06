#include "widget.h"
#include "ui_widget.h"
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QLabel* hw = new QLabel(this);
    hw->setText("hello world");
}

Widget::~Widget()
{
    delete ui;
}
