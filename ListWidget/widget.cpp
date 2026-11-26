#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("请输入需要添加的条目");
}

Widget::~Widget()
{
    delete ui;
}
void Widget::on_pushButton_add_clicked()
{
    if(ui->lineEdit->text()!="")
    {
        ui->listWidget->addItem(ui->lineEdit->text());
    }
}
void Widget::on_pushButton_del_clicked()
{
    int row = ui->listWidget->currentRow();
    if(row<0) return;
    else
    {
        ui->listWidget->takeItem(row);
    }
}

