#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->comboBox->addItem("辣椒炒肉盖饭");
    ui->comboBox->addItem("椒麻鸡盖饭");
    ui->comboBox->addItem("扬州炒饭");

    ui->comboBox_2->addItem("麻婆豆腐");
    ui->comboBox_2->addItem("烟熏肉");

    ui->comboBox_3->addItem("可乐");
    ui->comboBox_3->addItem("雪碧");
    ui->comboBox_3->addItem("芬达");

}

Widget::~Widget()
{
    delete ui;
}
