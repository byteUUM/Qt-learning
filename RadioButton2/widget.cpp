#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label_hint->hide();
    ui->label_print->hide();
    group1 = new QButtonGroup(this);
    group2 = new QButtonGroup(this);
    group3 = new QButtonGroup(this);

    group1->addButton(ui->radioButton);
    group1->addButton(ui->radioButton_2);
    group1->addButton(ui->radioButton_3);

    group2->addButton(ui->radioButton_4);
    group2->addButton(ui->radioButton_5);

    group3->addButton(ui->radioButton_6);
    group3->addButton(ui->radioButton_7);
    group3->addButton(ui->radioButton_8);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_radioButton_male_clicked(bool checked)
{
    if(checked) qDebug()<<"checked: true";
    else qDebug()<<"checked: false";
}

void Widget::on_radioButton_male_pressed()
{
    qDebug()<<"pressed";
}

void Widget::on_radioButton_male_released()
{
    qDebug()<<"released";
}

void Widget::on_radioButton_male_toggled(bool checked)
{
    if(checked) qDebug()<<"toggled: true";
    else qDebug()<<"toggled: false";
}


void Widget::on_pushButton_submit_clicked()
{
    ui->label_hint->show();
    QString menu;
    if(!group1->checkedButton())
    {
        ui->label_hint->setText("提交失败，请选择主食!");
        return;
    }
    menu += group1->checkedButton()->text()+",";

    if(!group2->checkedButton())
    {
        ui->label_hint->setText("提交失败，请选择配菜!");
        return;
    }
    menu += group2->checkedButton()->text()+",";

    if(!group3->checkedButton())
    {
        ui->label_hint->setText("提交失败，请选择饮品!");
        return;
    }
    menu += group3->checkedButton()->text();
    ui->label_hint->setText("提交成功!");
    ui->label_print->setText("你的选择是: "+menu);
    ui->label_print->setWordWrap(true);
    ui->label_print->show();
}

