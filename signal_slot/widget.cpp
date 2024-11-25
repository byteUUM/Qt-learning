#include "widget.h"
#include "ui_widget.h"
#include <QString>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(this,&Widget::Sign,this,&Widget::MySignal);
    emit Widget::Sign("title_1");
}

Widget::~Widget()
{
    delete ui;
}
void Widget::MySignal(const QString& s)
{
    this->setWindowTitle(s);
}

void Widget::on_pushButton_clicked()
{
    Widget::ui->pushButton->setText("按钮1已按下！");
}

void Widget::on_pushButton_2_clicked()
{
    Widget::ui->pushButton_2->setText("按钮2已按下！");
}
