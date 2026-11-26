#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置4行3列
    ui->tableWidget->setRowCount(4);
    ui->tableWidget->setColumnCount(3);

    //设置列名
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("姓名"));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("年龄"));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("班级"));

    ui->tableWidget->setItem(0,0,new QTableWidgetItem("李四"));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem("12"));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("12530"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_installRow_clicked()
{
    //获取现在有多少行
    int row = ui->tableWidget->rowCount();
    //添加行，这里传入的是新添加的下标
    ui->tableWidget->insertRow(row);
}
void Widget::on_pushButton_deleteRow_clicked()
{
    //获取当前选中的行号
    int row = ui->tableWidget->currentRow();
    //删除行
    ui->tableWidget->removeRow(row);
}
void Widget::on_pushButton_installColumn_clicked()
{
    int col = ui->tableWidget->columnCount();
    ui->tableWidget->insertColumn(col);
    QString text = ui->lineEdit->text();
    ui->tableWidget->setHorizontalHeaderItem(col,new QTableWidgetItem(text));
}

void Widget::on_pushButton_deleteColumn_clicked()
{
    int col = ui->tableWidget->currentColumn();
    ui->tableWidget->removeColumn(col);
}

