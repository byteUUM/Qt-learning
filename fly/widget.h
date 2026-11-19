#ifndef WIDGET_H
#define WIDGET_H

#include "qpushbutton.h"
#include <QWidget>
#include <list>
#include <QSoundEffect>

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
    void productBullet();
    //发射子弹
    void moveBullet();
    //生成导弹
    void productMissile();
    //发射导弹
    void moveMissile();

    void gameOver();
    void gameAgain();

    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

    void moveBird();

    ~Widget() override;
private slots:

    void on_pushButton_again_clicked();

    void on_pushButton_end_clicked();

    void info();

    void on_pushButton_stop_clicked();

private:
    //鸟配置
    QTimer* _mover_bird;
    int _bird_speed = 2;
    QSoundEffect *_bird_sound;


    //子弹配置
    std::list<QPushButton*> _bullets;
    QTimer* _pro_bullet;
    QTimer* _mover_bullet;
    //int _bullet_amount = 1;
    int _bullet_speed = 3;
    QSoundEffect *_bullet_sound;


    //火箭配置
    std::list<QPushButton*> _missiles;
    QTimer* _pro_missile;
    QTimer* _mover_missile;
    //int _missiles_amount = 1;
    int _missile_speed = 3;
    QSoundEffect *_missile_sound;

    QSet<int> _keys;
    QTimer* _time;
    int _count = 0;
    bool _isStop = true;
    Ui::Widget *ui;

    //爆炸
    QSoundEffect *_blast_sound;
};
#endif // WIDGET_H
