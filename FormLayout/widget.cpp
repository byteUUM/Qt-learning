#include "widget.h"
#include "ui_widget.h"
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QFormLayout* flayout = new QFormLayout(this);

    QLabel* lb1 = new QLabel("姓名");
    QLabel* lb2 = new QLabel("年龄");
    QLabel* lb3 = new QLabel("电话");

    QLineEdit* le1 = new QLineEdit();
    QLineEdit* le2 = new QLineEdit();
    QLineEdit* le3 = new QLineEdit();

    QPushButton* submit = new QPushButton("提交");

    flayout->addRow(lb1,le1);
    flayout->addRow(lb2,le2);
    flayout->addRow(lb3,le3);
    flayout->addRow(nullptr,submit);


}

Widget::~Widget()
{
    delete ui;
}
