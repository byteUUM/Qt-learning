#include "mylabel.h"
#include <QLabel>
#include <QDebug>
MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{}
MyLabel::~MyLabel()
{
    qDebug()<<"MyLabel 被释放";
}
