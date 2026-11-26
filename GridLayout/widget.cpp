#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPushButton* button1 = new QPushButton("按钮1");
    QPushButton* button2 = new QPushButton("按钮2");
    QPushButton* button3 = new QPushButton("按钮3");
    QPushButton* button4 = new QPushButton("按钮4");

    QGridLayout* glayout = new QGridLayout(this);
    glayout->addWidget(button1,0,0);
    glayout->addWidget(button2,1,1);
    glayout->addWidget(button3,2,2);
    glayout->addWidget(button4,0,2);

    glayout->setColumnStretch(0,1);
    glayout->setColumnStretch(1,2);
    glayout->setColumnStretch(2,1);

    button1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    button2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    button3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    button4->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

Widget::~Widget()
{
    delete ui;
}
