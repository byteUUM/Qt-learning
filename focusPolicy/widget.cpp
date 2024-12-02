#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_2->setFocusPolicy(Qt::TabFocus);
    ui->lineEdit_3->setFocusPolicy(Qt::ClickFocus);
    ui->lineEdit_4->setFocusPolicy(Qt::StrongFocus);
}

Widget::~Widget()
{
    delete ui;
}

