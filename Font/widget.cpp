#include "widget.h"
#include "ui_widget.h"
#include <qlabel.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QLabel* label = new QLabel(this);
    label->setText("i have to finish this project today");
    // 1. 创建 QFont 对象
    QFont font;

    // 2. 设置属性
    font.setFamily("微软雅黑");      // 设置字体家族
    font.setPointSize(14);           // 设置字号（点）
    font.setBold(true);              // 设置加粗
    font.setItalic(true);            // 设置斜体
    font.setUnderline(true);         // 设置下划线

    // 3. 应用到控件
    label->setFont(font);
}

Widget::~Widget()
{
    delete ui;
}
