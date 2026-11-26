#include "widget.h"
#include "ui_widget.h"

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
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,ui->lineEdit->text());
    ui->treeWidget->addTopLevelItem(item);
}


void Widget::on_pushButton_2_clicked()
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,ui->lineEdit->text());
    auto itemParent = ui->treeWidget->currentItem();
    itemParent->addChild(item);
}


void Widget::on_pushButton_3_clicked()
{
    auto item = ui->treeWidget->currentItem();
    //获取父元素通过父元素删除
    auto parent = item->parent();
    if(parent == nullptr)
    {
        //顶层元素删除
        //获取下标
        int index = ui->treeWidget->indexOfTopLevelItem(item);
        ui->treeWidget->takeTopLevelItem(index);
    }
    else
    {
        //非顶层元素删除
        parent->removeChild(item);
    }
}

