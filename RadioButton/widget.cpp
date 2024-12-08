#include "widget.h"
#include "ui_widget.h"
#include <QButtonGroup>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QButtonGroup* group1=new QButtonGroup(this);
    QButtonGroup* group2=new QButtonGroup(this);
    group1->addButton(ui->radioButton);
    group1->addButton(ui->radioButton_2);
    group1->addButton(ui->radioButton_3);
    group2->addButton(ui->radioButton_4);
    group2->addButton(ui->radioButton_5);
}

Widget::~Widget()
{
    delete ui;
}

