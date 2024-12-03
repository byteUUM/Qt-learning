#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QIcon icon(":/png/pp.png");
    ui->target->setIcon(icon);
    ui->target->setIconSize(QSize(200,200));

    ui->up->setIcon(QIcon(":/png/up.png"));
    ui->down->setIcon(QIcon(":/png/down.png"));
    ui->left->setIcon(QIcon(":/png/left.png"));
    ui->right->setIcon(QIcon(":/png/right.png"));

    ui->up->setShortcut(Qt::Key_Up);
    ui->down->setShortcut(Qt::Key_Down);
    ui->left->setShortcut(Qt::Key_Left);
    ui->right->setShortcut(Qt::Key_Right);

    ui->up->setAutoRepeat(true);
    ui->down->setAutoRepeat(true);
    ui->left->setAutoRepeat(true);
    ui->right->setAutoRepeat(true);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_up_clicked()
{
    QRect rect=ui->target->geometry();
    ui->target->setGeometry(rect.x(),rect.y()-20,rect.width(),rect.height());
}
void Widget::on_down_clicked()
{
    QRect rect=ui->target->geometry();
    ui->target->setGeometry(rect.x(),rect.y()+20,rect.width(),rect.height());
}
void Widget::on_left_clicked()
{
    QRect rect=ui->target->geometry();
    ui->target->setGeometry(rect.x()-20,rect.y(),rect.width(),rect.height());
}
void Widget::on_right_clicked()
{
    QRect rect=ui->target->geometry();
    ui->target->setGeometry(rect.x()+20,rect.y(),rect.width(),rect.height());
}
