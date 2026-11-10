#include "widget.h"
#include "ui_widget.h"
#include "QPushButton"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPushButton* button = new QPushButton(this);
    button->setText("close");
    button->move(300,300);
    connect(button,&QPushButton::clicked,this,&Widget::close);
    //connect(const Qobject *sender,
    //        const char * signal
    //        const Q0bject * receiver
    //        const char * method
    //        Qt::ConnectionType type = Qt::AutoConnection
    //)
}

Widget::~Widget()
{
    delete ui;
}
