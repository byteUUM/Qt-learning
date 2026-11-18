#include "widget.h"
#include "ui_widget.h"
#include <QThread>
#include <QTimer>
#include <QLabel>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    srand(time(NULL));
    this->setWindowTitle("弹隙飞鸟");
    QIcon title(":/png/fly.png");
    this->setWindowIcon(title);
    info();

    //设置快捷键
    // ui->pushButton_ctrl_up->setShortcut(QKeySequence("w"));
    // ui->pushButton_ctrl_down->setShortcut(QKeySequence("s"));
    // ui->pushButton_ctrl_left->setShortcut(QKeySequence("a"));
    // ui->pushButton_ctrl_right->setShortcut(QKeySequence("d"));

    //渲染
    QIcon iconwall = QIcon(":/png/wall.png");
    QIcon iconbird = QIcon(":/png/bird.png");
    ui->pushButton_bird->setIcon(iconbird);
    ui->pushButton_bird->setIconSize(QSize(ui->pushButton_bird->width(),ui->pushButton_bird->height()));

    ui->pushButton_wall_up->setStyleSheet("QPushButton {""background-color: red;""}");
    ui->pushButton_wall_down->setStyleSheet("QPushButton {""background-color: red;""}");
    ui->pushButton_over->setStyleSheet("QPushButton {""background-color: red;""};color:black;");
    ui->pushButton_over->hide();
    ui->pushButton_again->hide();
    ui->pushButton_end->hide();

    ui->pushButton_again->setEnabled(false);
    ui->pushButton_again->setEnabled(false);


    _pro = new QTimer(this);
    connect(_pro,&QTimer::timeout,this,&Widget::product);
    _pro->start(1000);

    _mover = new QTimer(this);
    connect(_mover,&QTimer::timeout,this,&Widget::running);
    _mover->start(20);

    _time = new QTimer(this);
    connect(_time,&QTimer::timeout,this,[this](){
        ++_count;
        if(_count==10) _bullet_amount++;
        if(_count==25) _bullet_amount++;
        if(_count==35) _fly_bullet++;
        ui->pushButton_time->setText("time:"+QString::number(_count));
    });
    _time->start(1000);

}

void Widget::keyPressEvent(QKeyEvent *e)   { if (!e->isAutoRepeat()) _keys.insert(e->key()); }
void Widget::keyReleaseEvent(QKeyEvent *e) { if (!e->isAutoRepeat()) _keys.remove(e->key()); }

void Widget::moveBird()
{
    int dx = _keys.contains(Qt::Key_D) - _keys.contains(Qt::Key_A);
    int dy = _keys.contains(Qt::Key_S) - _keys.contains(Qt::Key_W);
    if (!dx && !dy) return;
    auto *b = ui->pushButton_bird;
    int x = qBound(0, b->x() + dx * _fly_bird, width() - b->width());
    int y = b->y() + dy * _fly_bird;
    b->move(x, y);
    int top    = ui->pushButton_wall_up->geometry().bottom() + 1;
    int bottom = ui->pushButton_wall_down->y() - b->height();
    if (y <= top || y >= bottom)
    {
        _pro->stop();
        _mover->stop();
        _time->stop();
        ui->pushButton_over->show();
        ui->pushButton_again->show();
        ui->pushButton_end->show();
        ui->pushButton_again->setEnabled(true);
        ui->pushButton_end->setEnabled(true);
    }
}

void Widget::product()
{
    for(int i = 0;i<_bullet_amount;i++)
    {
        QPushButton* blt = new QPushButton(this);

        int width = 21;
        int height = 16;
        //调整出场位置和大小
        //Y轴上边界
        int edgeYUp=ui->pushButton_wall_up->y()+ui->pushButton_wall_up->height();

        //Y轴下边界
        int edgeYDown = ui->pushButton_wall_down->y()-height;

        //X轴固定点位 this->width()
        blt->setGeometry(this->width()
                        ,edgeYUp+rand()%(edgeYDown-edgeYUp)
                        ,width,height
                        );

        //渲染
        QIcon iconbullet = QIcon(":/png/bullet.png");
        blt->setIcon(iconbullet);
        blt->setIconSize(QSize(blt->width(),blt->height()));

        //因为这是在widget创建完exec时才可能执行所以要手动show
        blt->show();
        this->_bullets.push_back(blt);
    }
}

void Widget::running()
{
    moveBird();
    for(auto it=_bullets.begin();it!=_bullets.end();)
    {
        QPushButton* blt = *it;
        int x = blt->geometry().x();
        int y = blt->geometry().y();
        blt->move(x-_fly_bullet,y);
        int birdxr=ui->pushButton_bird->x()+ui->pushButton_bird->width();
        int bulletxl = blt->x();
        int bulletxr = blt->x()+blt->width();

        int birdyu = ui->pushButton_bird->y();
        int birdyd = ui->pushButton_bird->y()+ui->pushButton_bird->height();
        int bulletyu = blt->y();
        int bulletyd = blt->y()+blt->height();

        if(birdxr>bulletxl&&birdxr<bulletxr)
        {
            if((birdyu>bulletyu&&birdyu<bulletyd)
                ||(birdyd>bulletyu&&birdyd<bulletyd)
                ||(bulletyu>birdyu&&bulletyd<birdyd))
            {
                _pro->stop();
                _mover->stop();
                _time->stop();
                ui->pushButton_over->show();
                ui->pushButton_again->show();
                ui->pushButton_end->show();
                ui->pushButton_again->setEnabled(true);
                ui->pushButton_end->setEnabled(true);

            }

        }
        //判断是否出界
        if(x<=0)
        {
            blt->deleteLater();
            it = _bullets.erase(it);
        }
        else it++;
    }
}

Widget::~Widget()
{
    delete ui;
}

// void Widget::on_pushButton_ctrl_up_clicked()
// {
//     int egdeYUp = ui->pushButton_wall_up->y()+ui->pushButton_wall_up->height();
//     ui->pushButton_bird->move(ui->pushButton_bird->x(),ui->pushButton_bird->y()-FLY);
//     if(ui->pushButton_bird->y()<=egdeYUp)
//     {
//         this->close();
//     }
// }

// void Widget::on_pushButton_ctrl_down_clicked()
// {
//     int egdeYDown = ui->pushButton_wall_down->y()-ui->pushButton_bird->height();
//     ui->pushButton_bird->move(ui->pushButton_bird->x(),ui->pushButton_bird->y()+FLY);
//     if(ui->pushButton_bird->y()>=egdeYDown)
//     {
//         this->close();
//     }
// }

// void Widget::on_pushButton_ctrl_left_clicked()
// {
//     int egdeXLeft = 0;
//     if(ui->pushButton_bird->x()-FLY<egdeXLeft) return;
//     ui->pushButton_bird->move(ui->pushButton_bird->x()-FLY,ui->pushButton_bird->y());
// }


// void Widget::on_pushButton_ctrl_right_clicked()
// {
//     int egdeXRight = this->width();
//     if(ui->pushButton_bird->x()+FLY>egdeXRight) return;
//     ui->pushButton_bird->move(ui->pushButton_bird->x()+FLY,ui->pushButton_bird->y());
// }


void Widget::on_pushButton_again_clicked()
{
    ui->pushButton_over->hide();
    ui->pushButton_end->hide();
    ui->pushButton_again->hide();
    ui->pushButton_again->setEnabled(false);
    ui->pushButton_end->setEnabled(false);
    ui->pushButton_bird->move(170,60);
    info();
    _pro->start();
    _mover->start();
    _time->start();
}


void Widget::on_pushButton_end_clicked()
{
    Widget::close();
}

void Widget::info()
{
    _bullet_amount = 1;
    _fly_bullet = 3;
    _fly_bird = 4;
    _count = 0;
}

