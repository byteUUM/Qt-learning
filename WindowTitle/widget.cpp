#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("windowTitle");
    QPushButton* button = new QPushButton(this);
    //button->setWindowTitle("button");
}

Widget::~Widget()
{
    delete ui;
}
