#include "widget.h"
#include "ui_widget.h"
#include <QIcon>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QIcon icon(":/egg.png");
    this->setWindowIcon(icon);
}

Widget::~Widget()
{
    delete ui;
}
