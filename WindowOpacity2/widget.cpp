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

void Widget::on_pushButton_add_clicked()
{
    this->setWindowOpacity(this->windowOpacity()+0.125);
}
void Widget::on_pushButton_sub_clicked()
{
    this->setWindowOpacity(this->windowOpacity()-0.125);
}

