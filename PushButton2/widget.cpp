#include "widget.h"
#include "ui_widget.h"
#include <QIcon>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QIcon icon = QIcon(":/work.png");
    ui->pushButton->setIcon(icon);
    ui->pushButton->setText("工作台");

    ui->pushButton->setShortcut(QKeySequence("o"));

}
Widget::~Widget()
{
    delete ui;
}
void Widget::on_pushButton_clicked()
{
    ui->pushButton->setText("槽函数被执行");
}

