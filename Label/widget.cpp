#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label->setTextFormat(Qt::PlainText);
    ui->label->setText("**这是**一段纯<u>文本</u>");

    ui->label_2->setTextFormat(Qt::RichText);
    ui->label_2->setText("**这是**一段富<u>文本</u>");

    ui->label_3->setTextFormat(Qt::MarkdownText);
    ui->label_3->setText("**这是**一段markdown<u>文本</u>");


}


Widget::~Widget()
{
    delete ui;
}
