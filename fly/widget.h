#ifndef WIDGET_H
#define WIDGET_H

#include "qpushbutton.h"
#include <QWidget>
#include <list>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    //生成子弹
    void product();

    //发射子弹
    void running();

    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

    void moveBird();

    ~Widget() override;
private slots:

    void on_pushButton_again_clicked();

    void on_pushButton_end_clicked();

    void info();

private:
    std::list<QPushButton*> _bullets;
    QSet<int> _keys;
    QTimer* _pro;
    QTimer* _mover;
    QTimer* _time;
    int _count = 0;
    Ui::Widget *ui;
    int _bullet_amount = 1;
    int _fly_bullet = 3;
    int _fly_bird = 2;
};
#endif // WIDGET_H
