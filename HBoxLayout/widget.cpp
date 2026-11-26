#include "widget.h"
#include "ui_widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    //水平管理器先不挂对象树，到时候挂到垂直管理器下
    QHBoxLayout* hlayout = new QHBoxLayout(this);

    QPushButton* button1 = new QPushButton("按钮1");
    QPushButton* button2 = new QPushButton("按钮2");
    vlayout->addWidget(button1);
    vlayout->addWidget(button2);

    QPushButton* button3 = new QPushButton("按钮3");
    QPushButton* button4 = new QPushButton("按钮4");
    hlayout->addWidget(button3);
    hlayout->addWidget(button4);

    vlayout->addLayout(hlayout);
}

Widget::~Widget()
{
    delete ui;
}
