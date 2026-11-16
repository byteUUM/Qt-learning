#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QIcon>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPixmap pixel(":/pen.png");
    pixel = pixel.scaled(20,20);
    auto x = QCursor(pixel,0,20);
    this->setCursor(x);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ui->pushButton->setText("Welcome home conwy!");
}

