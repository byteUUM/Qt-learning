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
    if(ui->pushButton->text()==QString("begin"))
        ui->pushButton->setText("end");
    else ui->pushButton->setText("begin");
}

void Widget::on_pushButton_2_clicked()
{
    if(ui->pushButton->isEnabled())
        ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
}
