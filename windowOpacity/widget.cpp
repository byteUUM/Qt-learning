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
    auto val=windowOpacity();
    val+=0.1;
    setWindowOpacity(val);
}
void Widget::on_pushButton_2_clicked()
{
    auto val=windowOpacity();
    if(val>0.1) val-=0.1;
    setWindowOpacity(val);
}
