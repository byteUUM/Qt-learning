#include "widget.h"
#include "ui_widget.h"
#include <QFont>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QFont font;
    font.setFamily("宋体");
    font.setBold(true);
    font.setPixelSize(20);
    font.setUnderline(true);
    font.setItalic(true);
    font.setStrikeOut(true);
    ui->label->setFont(font);
    ui->pushButton->setToolTip("别点击我");
    ui->pushButton->setToolTipDuration(3000);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    if(ui->pushButton->text()==QString("begin"))
    {
        ui->pushButton->setText("end");
    }
    else
    {
        ui->pushButton->setText("begin");
    }
}
