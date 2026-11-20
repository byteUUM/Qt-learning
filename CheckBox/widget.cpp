#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label->setWordWrap(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_submit_clicked()
{
    QString str;
    if(ui->checkBox_study->isChecked())
        str+=ui->checkBox_study->text()+" ";
    if(ui->checkBox_game->isChecked())
        str+=ui->checkBox_game->text()+" ";
    if(ui->checkBox_movie->isChecked())
        str+=ui->checkBox_movie->text();
    ui->label->setText("今天的计划是: "+str);
}

