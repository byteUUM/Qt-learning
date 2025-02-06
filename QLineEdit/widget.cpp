#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEditg_name->setPlaceholderText("请输入姓名");
    ui->lineEditg_name->setClearButtonEnabled(true);

    ui->lineEdit_password->setPlaceholderText("请输入密码");
    ui->lineEdit_password->setClearButtonEnabled(true);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    ui->lineEdit_phone->setPlaceholderText("请输入电话");
    ui->lineEdit_phone->setClearButtonEnabled(true);
}

Widget::~Widget()
{
    delete ui;
}

