#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QVBoxLayout>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //先不挂到对象树，到时候放在布局管理器下
    QPushButton* button1 = new QPushButton("按钮1");
    QPushButton* button2 = new QPushButton("按钮2");
    QPushButton* button3 = new QPushButton("按钮3");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(button1);//自动把Button对象挂在Layout下
    layout->addWidget(button2);
    layout->addWidget(button3);
}

Widget::~Widget()
{
    delete ui;
}
