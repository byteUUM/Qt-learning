#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPushButton* button = new QPushButton(this);
    button->setText("click");
    button->move(300,300);
    button->setToolTip("测试按钮");
    button->setToolTipDuration(3000);
}

Widget::~Widget()
{
    delete ui;
}
