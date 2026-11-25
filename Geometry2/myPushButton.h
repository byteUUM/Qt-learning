#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit myPushButton(QWidget *parent = nullptr);
    void virtual enterEvent(QEnterEvent* event);
signals:
    void entered();
signals:
};

#endif // MYPUSHBUTTON_H
