#include "widget.h"
#include "ui_widget.h"
#include <QThread>
#include <QTimer>
#include <QLabel>
#include <QKeyEvent>
#include <QDebug>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <climits>

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

    //声音
    _bird_sound = new QSoundEffect(this);
    _bird_sound->setSource(QUrl("qrc:/sound/birdSound.mp3"));
    _bird_sound->setVolume(1);
    _bullet_sound = new QSoundEffect(this);
    _bullet_sound->setSource(QUrl("qrc:/sound/bulletSound.mp3"));
    _bullet_sound->setVolume((float)0.3);
    _missile_sound = new QSoundEffect(this);
    _missile_sound->setSource(QUrl("qrc:/sound/missileSound.mp3"));
    _missile_sound->setVolume((float)0.4);
    _blast_sound = new QSoundEffect(this);
    _blast_sound->setSource(QUrl("qrc:/sound/blastSound.mp3"));
    _blast_sound->setVolume((float)0.5);
    //背景音
    auto *player = new QMediaPlayer(this);// 0.05
    auto *out = new QAudioOutput(this);
    player->setAudioOutput(out);
    out->setVolume((float)0.1);
    player->setSource(QUrl("qrc:/sound/backGroundSound.mp3"));
    player->setLoops(QMediaPlayer::Infinite);      // 循环播放
    player->play();

    //渲染
    QIcon iconbird = QIcon(":/png/bird.png");
    QIcon iconblast = QIcon(":/png/blast.png");
    ui->pushButton_bird->setIcon(iconbird);
    ui->pushButton_bird->setIconSize(QSize(ui->pushButton_bird->width(),ui->pushButton_bird->height()));
    ui->pushButton_blast->setIcon(iconblast);

    ui->pushButton_wall_up->setStyleSheet("QPushButton {""background-color: red;""}");
    ui->pushButton_wall_down->setStyleSheet("QPushButton {""background-color: red;""}");
    ui->pushButton_over->setStyleSheet("QPushButton {""background-color: red;""};color:black;");
    ui->pushButton_over->hide();
    ui->pushButton_again->hide();
    ui->pushButton_end->hide();
    ui->pushButton_blast->hide();

    ui->pushButton_again->setEnabled(false);
    ui->pushButton_again->setEnabled(false);

    ui->pushButton_stop->setToolTip("空格键暂停");
    ui->pushButton_stop->setShortcut(QKeySequence("Space"));


    _pro_bullet = new QTimer(this);
    connect(_pro_bullet,&QTimer::timeout,this,&Widget::productBullet);
    _pro_bullet->start(1000);

    _mover_bullet = new QTimer(this);
    connect(_mover_bullet,&QTimer::timeout,this,&Widget::moveBullet);
    _mover_bullet->start(20);

    _pro_missile = new QTimer(this);
    connect(_pro_missile,&QTimer::timeout,this,&Widget::productMissile);
    _pro_missile->start(INT_MAX);

    _mover_missile = new QTimer(this);
    connect(_mover_missile,&QTimer::timeout,this,&Widget::moveMissile);
    _mover_missile->start(INT_MAX);

    _mover_bird = new QTimer(this);
    connect(_mover_bird,&QTimer::timeout,this,&Widget::moveBird);
    _mover_bird->start(20);

    //统计时间，根据时间增加难度
    _time = new QTimer(this);
    connect(_time,&QTimer::timeout,this,[this](){
        ++_count;
        if(_count==10) _pro_bullet->setInterval(700);
        //if(_count==35) _mover_bullet->setInterval(14);
        if(_count==15)
        {
            _pro_missile->start(1000);
            _mover_missile->start(25);
        }
        if(_count==25) _pro_bullet->setInterval(500);
        if(_count==60)
        {
            _pro_bullet->setInterval(400);
            _pro_missile->start(700);
        }
        if(_count==120) _pro_bullet->setInterval(200);
        ui->pushButton_time->setText("time:"+QString::number(_count));
    });
    _time->start(1000);

}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->isAutoRepeat()) return;
    _keys.insert(e->key());
    _bird_sound->play();
}
void Widget::keyReleaseEvent(QKeyEvent *e) { if (!e->isAutoRepeat()) _keys.remove(e->key()); }

void Widget::moveBird()
{
    int dx = _keys.contains(Qt::Key_D) - _keys.contains(Qt::Key_A);
    int dy = _keys.contains(Qt::Key_S) - _keys.contains(Qt::Key_W);
    if (!dx && !dy) return;
    auto *b = ui->pushButton_bird;
    int x = qBound(0, b->x() + dx * _bird_speed, width() - b->width());
    int y = b->y() + dy * _bird_speed;
    b->move(x, y);
    int top    = ui->pushButton_wall_up->geometry().bottom() + 1;
    int bottom = ui->pushButton_wall_down->y() - b->height();
    if (y < top-8 || y > bottom+8)
    {
        gameOver();
    }
}

void Widget::productBullet()
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

    _bullet_sound->play();

}

void Widget::moveBullet()
{
    for(auto it=_bullets.begin();it!=_bullets.end();)
    {
        QPushButton* blt = *it;
        int x = blt->geometry().x();
        int y = blt->geometry().y();
        blt->move(x-_bullet_speed,y);
        int birdxr=ui->pushButton_bird->x()+ui->pushButton_bird->width();
        int bulletxl = blt->x();
        int bulletxr = blt->x()+blt->width();

        int birdyu = ui->pushButton_bird->y();
        int birdyd = ui->pushButton_bird->y()+ui->pushButton_bird->height();
        int bulletyu = blt->y();
        int bulletyd = blt->y()+blt->height();

        if(birdxr>bulletxl+5&&birdxr<bulletxr-5)
        {
            if((birdyu>bulletyu+3&&birdyu<bulletyd-3)
                ||(birdyd>bulletyu+3&&birdyd<bulletyd-3)
                ||(bulletyu>birdyu&&bulletyd<birdyd))
            {
                ui->pushButton_blast->show();
                _blast_sound->play();
                ui->pushButton_blast->setGeometry(blt->x(),blt->y(),blt->width(),blt->height());
                ui->pushButton_blast->setIconSize(QSize(blt->width(),blt->height()));
                blt->hide();
                gameOver();
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

void Widget::productMissile()
{
    QPushButton* missile = new QPushButton(this);

    int width = 31;
    int height = 31;
    //调整出场位置和大小
    //Y轴固定点
    int Y=ui->pushButton_wall_down->y();

    //X轴左边界
    int edgeXLeft = 0;

    //X轴右边界
    int edgeXRight = this->width();

    missile->setGeometry(edgeXLeft+rand()%(edgeXRight-edgeXLeft)
                     ,Y
                     ,width,height
                     );

    //渲染
    QIcon iconmissile = QIcon(":/png/missile.png");
    missile->setIcon(iconmissile);
    missile->setIconSize(QSize(missile->width(),missile->height()));

    //因为这是在widget创建完exec时才可能执行所以要手动show
    missile->show();
    this->_missiles.push_back(missile);

    _missile_sound->play();
}

void Widget::moveMissile()
{
    for(auto it=_missiles.begin();it!=_missiles.end();)
    {
        QPushButton* missile = *it;
        int x = missile->geometry().x();
        int y = missile->geometry().y();
        missile->move(x+_missile_speed,y-_missile_speed);
        int birdxr=ui->pushButton_bird->x()+ui->pushButton_bird->width();
        int birdxl=ui->pushButton_bird->x();
        //int birdyu = ui->pushButton_bird->y();
        int birdyd = ui->pushButton_bird->y()+ui->pushButton_bird->height();

        int missilexl = missile->x();
        int missilexr = missile->x()+missile->width();
        int missileyu = missile->y();
        int missileyd = missile->y()+missile->height();

        if(birdyd>missileyu+10&&birdyd<missileyd-10)
        {
            if((birdxl>missilexl+8&&birdxl<missilexr-8)
                ||(birdxr>missilexl+8&&birdxr<missilexr-8)
                ||(birdxl>missilexl&&birdxr<missilexr))
            {
                ui->pushButton_blast->show();
                _blast_sound->play();
                ui->pushButton_blast->move(missile->x(),missile->y());
                ui->pushButton_blast->setIconSize(QSize(missile->width(),missile->height()));
                missile->hide();
                gameOver();
            }

        }
        //判断是否出界
        if(y<=0)
        {
            missile->deleteLater();
            it = _missiles.erase(it);
        }
        else it++;
    }
}
void Widget::gameOver()
{
    _pro_bullet->stop();
    _pro_missile->stop();
    _mover_bird->stop();
    _mover_bullet->stop();
    _mover_missile->stop();
    _time->stop();

    ui->pushButton_over->show();
    ui->pushButton_again->show();
    ui->pushButton_end->show();
    ui->pushButton_again->setEnabled(true);
    ui->pushButton_end->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
}
void Widget::gameAgain()
{
    for(auto it:_bullets)
        it->deleteLater();
    for(auto it:_missiles)
        it->deleteLater();
    _bullets.clear();
    _missiles.clear();

    ui->pushButton_over->hide();
    ui->pushButton_end->hide();
    ui->pushButton_again->hide();
    ui->pushButton_blast->hide();
    ui->pushButton_again->setEnabled(false);
    ui->pushButton_end->setEnabled(false);
    ui->pushButton_bird->move(170,60);
    info();
    _pro_bullet->setInterval(1000);
    _mover_bullet->setInterval(20);
    _mover_bird->setInterval(20);
    _time->setInterval(1000);
    _pro_missile->setInterval(INT_MAX);
    _mover_missile->setInterval(INT_MAX);

    _pro_bullet->start();
    _mover_bullet->start();
    _time->start();
    _mover_bird->start();

    ui->pushButton_stop->setEnabled(true);
}


Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_again_clicked()
{
    gameAgain();
}


void Widget::on_pushButton_end_clicked()
{
    Widget::close();
}

void Widget::info()
{
    _bullet_speed = 3;
    _bird_speed = 4;
    _missile_speed = 2;
    _count = 0;
    ui->pushButton_time->setText("time:0");
}


void Widget::on_pushButton_stop_clicked()
{
    if(_isStop)
    {
        gameOver();
        ui->pushButton_over->hide();
        ui->pushButton_stop->setEnabled(true);
        _isStop = false;
    }
    else
    {
        _isStop = true;
        _pro_bullet->start();
        _pro_missile->start();
        _mover_bird->start();
        _mover_bullet->start();
        _mover_missile->start();
        _time->start();
        ui->pushButton_end->hide();
        ui->pushButton_again->hide();
        ui->pushButton_again->setEnabled(false);
        ui->pushButton_end->setEnabled(false);
    }
}

