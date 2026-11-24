#include "widget.h"
#include "ui_widget.h"
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEdit_name->setPlaceholderText("请输入您的姓名");
    ui->lineEdit_name->setClearButtonEnabled(true);

    ui->lineEdit_password->setPlaceholderText("请输入您的密码");
    ui->lineEdit_password->setClearButtonEnabled(true);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);//不显示密码

    ui->lineEdit_phoneNumber->setPlaceholderText("请输入您的电话号码");
    ui->lineEdit_phoneNumber->setClearButtonEnabled(true);


    QRegularExpression regExp("^1\\d{10}$");
    QValidator *validator = new QRegularExpressionValidator(regExp, this);
    ui->lineEdit_phoneNumber->setValidator(validator);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_lineEdit_phoneNumber_textChanged(const QString &arg1)
{
    QString str = arg1;
    int pos = 0;
    if(ui->lineEdit_phoneNumber->validator()->validate(str,pos) == QValidator::Acceptable)
    {
        ui->pushButton_submit->setEnabled(true);
    }
    else
    {
        ui->pushButton_submit->setEnabled(false);
    }
}

