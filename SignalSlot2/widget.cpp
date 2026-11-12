#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(this,&Widget::mySignal,this,&Widget::handleMySignal);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::handleMySignal(const QString& str)
{
    this->setWindowTitle(str);
}
void Widget::on_pushButton_1_clicked()
{
    mySignal("标题1","");
}
void Widget::on_pushButton_2_clicked()
{
    mySignal("标题2","");
}

