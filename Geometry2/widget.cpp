#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButton_conwy->hide();
    ui->pushButton_mark->hide();
    ui->pushButton_ask->hide();
    srand(time(NULL));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_up_clicked()
{
    QRect rect = ui->pushButton_target->geometry();
    if(rect.y()>0)
        rect.setY(rect.y()-5);
    ui->pushButton_target->setGeometry(rect);
}

void Widget::on_pushButton_down_clicked()
{
    QRect rect = ui->pushButton_target->geometry();
    if(rect.y()<this->height())
        rect.setY(rect.y()+5);
    ui->pushButton_target->setGeometry(rect);
}

void Widget::on_pushButton_left_clicked()
{
    QRect rect = ui->pushButton_target->geometry();
    if(rect.x()>0)
        rect.setX(rect.x()-5);
    ui->pushButton_target->setGeometry(rect);
}

void Widget::on_pushButton_right_clicked()
{
    QRect rect = ui->pushButton_target->geometry();
    if(rect.x()<this->width())
        rect.setX(rect.x()+5);
    ui->pushButton_target->setGeometry(rect);
}


// void Widget::on_pushButton_up_clicked()
// {
//     QRect rect = ui->pushButton_target->geometry();
//     if(rect.y()-5>=0)
//         ui->pushButton_target->setGeometry(rect.x(),rect.y()-5,rect.width(),rect.height());
// }

// void Widget::on_pushButton_down_clicked()
// {
//     QRect rect = ui->pushButton_target->geometry();
//     if(rect.y()+5<=this->height())
//         ui->pushButton_target->setGeometry(rect.x(),rect.y()+5,rect.width(),rect.height());
// }


// void Widget::on_pushButton_left_clicked()
// {
//     QRect rect = ui->pushButton_target->geometry();
//     if(rect.x()-5>=0)
//         ui->pushButton_target->setGeometry(rect.x()-5,rect.y(),rect.width(),rect.height());
// }


// void Widget::on_pushButton_right_clicked()
// {
//     QRect rect = ui->pushButton_target->geometry();
//     if(rect.x()+5<=this->width())
//         ui->pushButton_target->setGeometry(rect.x()+5,rect.y(),rect.width(),rect.height());
// }


void Widget::on_pushButton_conwy_clicked()
{
    ui->pushButton_ask->setText("it is conwy!");
    ui->pushButton_mark->setEnabled(false);
}

void Widget::on_pushButton_mark_clicked()
{
    ui->pushButton_mark->move(rand()%(this->width()-ui->pushButton_mark->width())
                              ,rand()%(this->height()-ui->pushButton_mark->height()));
}


void Widget::on_pushButton_mark_pressed()
{
    ui->pushButton_mark->move(rand()%(this->width()-ui->pushButton_mark->width())
                              ,rand()%(this->height()-ui->pushButton_mark->height()));
}

