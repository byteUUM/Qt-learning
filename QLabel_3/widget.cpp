#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置对齐方式
    ui->label->setAlignment(Qt::AlignCenter);

    //
    ui->label_2->setText("解耦股若经过荣辱观解决哦恶评开票费v喜酒偶觉得iv俄日");
    ui->label_2->setWordWrap(true);

    //缩进
    ui->label_3->setIndent(50);

    //边距
    ui->label_4->setMargin(30);

    ui->label_5->setBuddy(ui->radioButton);
    ui->label_6->setBuddy(ui->radioButton_2);
}

Widget::~Widget()
{
    delete ui;
}

