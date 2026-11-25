#include "myPushButton.h"

myPushButton::myPushButton(QWidget *parent)
    : QPushButton{parent}
{}

void myPushButton::enterEvent(QEnterEvent* event)
{
    emit entered();
}
//除了信号外的其他方式
// myPushButton.h
// QPushButton *target = nullptr;

// // widget.cpp
// ui->pushButton_move->target = ui->pushButton_mark;

// // myPushButton.cpp
// void myPushButton::enterEvent(QEvent *) {
//     if (!target) return;
//     QWidget *p = parentWidget();
//     target->move(rand() % (p->width() - target->width()),
//                  rand() % (p->height() - target->height()));
// }


//auto *mark = parentWidget()->findChild<QPushButton*>("pushButton_mark");