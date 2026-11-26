#include "widget.h"
#include "ui_widget.h"
#include <QLabel>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    //获取标签个数
    int count = ui->tabWidget->count()+1;
    QWidget* w = new QWidget();
    ui->tabWidget->addTab(w,"Tab "+QString::number(count));

    //添加控件
    QLabel* lb = new QLabel(w);
    lb->setText("标签页： "+QString::number(count));
    lb->resize(100,50);

    //设置当前选i中标签页
    ui->tabWidget->setCurrentIndex(count-1);
}

void Widget::on_pushButton_2_clicked()
{
    //获取选中的标签页下标
    int index = ui->tabWidget->currentIndex();
    //删除标签页
    ui->tabWidget->removeTab(index);
}

