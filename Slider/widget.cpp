#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(100, 1000);
    ui->horizontalSlider->setSingleStep(10);
    ui->horizontalSlider->setValue(800);

    ui->verticalSlider->setRange(100, 1000);
    ui->verticalSlider->setSingleStep(10);
    ui->verticalSlider->setValue(600);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_verticalSlider_valueChanged(int value)
{
    resize(width(),value);
}
void Widget::on_horizontalSlider_valueChanged(int value)
{
    resize(value,height());
}

