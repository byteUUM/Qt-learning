#include "widget.h"
#include "ui_widget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QHBoxLayout* hlayout = new QHBoxLayout(this);

    QPushButton* button1 = new QPushButton("按钮1");
    QPushButton* button2 = new QPushButton("按钮2");
    QSpacerItem* spacer1 = new QSpacerItem(200,20);

    hlayout->addWidget(button1);
    hlayout->addSpacerItem(spacer1);
    hlayout->addWidget(button2);
}

Widget::~Widget()
{
    delete ui;
}
