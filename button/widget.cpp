#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPushButton* button2=new QPushButton(this);
    button2->setText("button2");
    //
    ui->button1->setText("begin");
    connect(ui->button1,&QPushButton::clicked,this,&Widget::funbutton);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::funbutton()
{
    if(ui->button1->text()==QString("begin"))
    {
        ui->button1->setText("end");
    }
    else
    {
        ui->button1->setText("begin");
    }
}

void Widget::on_button3_clicked()
{
    this->setWindowTitle("按钮已经按下！");
}
