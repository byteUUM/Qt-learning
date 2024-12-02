#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    QCursor cursor(Qt::ForbiddenCursor);
//    ui->pushButton->setCursor(cursor);
    QPixmap png(":rose.png");
    png = png.scaled(40,40);
    QCursor cursor(png,10,10);
    ui->pushButton->setCursor(cursor);
}

Widget::~Widget()
{
    delete ui;
}

