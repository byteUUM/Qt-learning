#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>
#include <QGuiApplication>
#include <QScreen>
#include <QShortcut>
#include <QLabel>
#include <QMovie>
#include <QMediaPlayer>
#include <QAudioOutput>

Widget::Widget(QWidget *parent, bool isMainWindow, Widget* root)
    : QWidget(parent)
    , _root(isMainWindow ? this : root)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //快捷键退出程序
    QShortcut* sc = new QShortcut(this);
    sc->setKey(QKeySequence("Ctrl+Alt+K"));
    connect(sc,&QShortcut::activated,this,[this](){
        if(_root->_timer) _root->_timer->stop();
        _root->windowClear();
        qApp->quit();
    });

    if(!isMainWindow) return;

    //窗口图像
    // QPixmap pix = QPixmap(":/png/emesis.png");
    // QLabel* lb = new QLabel(this);
    // lb->setGeometry(0,0,this->width(),this->height());
    // lb->setPixmap(pix);
    // lb->setScaledContents(true);

    //动图设置
    QLabel* lb = new QLabel(this);
    lb->setGeometry(0,0,this->width(),this->height());
    auto *movie = new QMovie(":/png/emesis2.gif");
    movie->setParent(lb);//挂对象树，防止内存泄漏
    lb->setMovie(movie);
    movie->start();
    lb->setScaledContents(true);
    //启动声音
    _emesisSound = new QSoundEffect(this);
    _emesisSound->setSource(QUrl("qrc:/sound/emesis.mp3"));
    _emesisSound->setVolume((float)1);
    _emesisSound->play();


    //窗口生成定时器
    _timer = new QTimer(this);
    connect(_timer,&QTimer::timeout,this,&Widget::proWindow);
    _timer->start(1000);
    //窗口背景
    this->setStyleSheet("background-color: black;");

    //计数器,统计过去了多少时间
    _count = new QTimer(this);
    connect(_count,&QTimer::timeout,this,[=](){
        _timePasses++;
    });
    _count->start(1000);

    //计算显示屏大小
    QScreen *screen = QGuiApplication::primaryScreen();   // 主显示器
    QRect rect = screen->geometry();                      // 整个屏幕
    _MainW = rect.width();
    _MainH = rect.height();

    //随时数种子
    srand(time(NULL));

    //背景音
    backGroundSound(_clown_player1,QUrl("qrc:/sound/clown.mp3"),1);
    backGroundSound(_clown_player2,QUrl("qrc:/sound/clown.mp3"),1);
    backGroundSound(_clown_player3,QUrl("qrc:/sound/clown.mp3"),1);
    backGroundSound(_block2_player,QUrl("qrc:/sound/block2.mp3"),1);
    backGroundSound(_block10_player,QUrl("qrc:/sound/block10.mp3"),1);
    backGroundSound(_clown2_player1,QUrl("qrc:/sound/clown2.mp3"),1);

    // //动态解码以及缓存
    // _clownMovie = new QMovie(":/png/clown.gif", QByteArray(), this);
    // _clownMovie->setCacheMode(QMovie::CacheAll);   // 缓存已解码帧，循环播放不再重复解码
    // _clownMovie->start();
}


void Widget::proWindow()
{
    if(_timePasses<=0)
    {
        _emesisSound->play();
        return;
    }
    if(_timePasses>60) return;
    // 1. 一次性事件（每秒只触发一次）
    if(_timePasses != _lastTick)
    {
        _lastTick = _timePasses;
        if(_timePasses==1) _clown_player1->play();
        if(_timePasses==2) _clown2_player1->play();
        if(_timePasses==3) _timer->setInterval(100);
        if(_timePasses==4) _clown_player2->play();
        if(_timePasses==6) _clown_player3->play();
        if(_timePasses==5) _timer->setInterval(1000);
        if(_timePasses==20) _timer->setInterval(500);
        if(_timePasses==25) _block2_player->play();

        // 2. 蓝屏：单独处理，处理完直接 return
        if(_timePasses==60)
        {
            windowClear();
            _timer->stop();
            _clown_player1->stop();
            _clown_player2->stop();
            _clown_player3->stop();
            _block10_player->play();
            Widget* w = new Widget(nullptr,false,this);
            w->setStyleSheet("background-color: red;");
            w->showFullScreen();
            _widgets.push_back(w);
            //隐藏鼠标
            w->setCursor(Qt::BlankCursor);
            return;
        }
    }

    // 3. 超过 25 秒后，每生成一个删一个最老的（每次都执行）
    if(_timePasses>=25 && !_widgets.empty())
    {
        if(_widgets.front()) _widgets.front()->deleteLater();
        _widgets.pop_front();
    }

    // 4. 正常生成 clown 窗口（每次都执行）
    Widget* w = new Widget(nullptr,false,this);
    //窗口生成轨迹
    track(w);

    //窗口图标
    w->setWindowIcon(QIcon(":/png/emesis.png"));
    w->setWindowTitle("clown");
    //窗口背景
    w->setStyleSheet("background-color: #0f1a14;");//深绿色

    QLabel* label = new QLabel(w);
    label->setGeometry(0,0,_width,_height);
    auto *movie = new QMovie(":/png/clown.gif", QByteArray(), label);
    label->setMovie(movie);
    label->setScaledContents(true);
    movie->start();
    // if(_timePasses>20) //非同步
    // {
        // auto *movie = new QMovie(":/png/clown.gif", QByteArray(), label);
        // label->setMovie(movie);
        // label->setScaledContents(true);
        // movie->start();
    // }
    // else //同步
    // {
    //     label->setMovie(_clownMovie);
    //     label->setScaledContents(true);
    // }

    _widgets.push_back(w);
    w->show();
}

void Widget::windowClear()
{
    for(auto x:_widgets)
    {
        if(x) x->deleteLater();
    }
    _widgets.clear();
}

void Widget::backGroundSound(QMediaPlayer*& player, QUrl url, float volume)
{
    player = new QMediaPlayer(this);
    auto *out = new QAudioOutput(this);
    player->setAudioOutput(out);
    out->setVolume((float)volume);
    player->setSource(url);
    player->setLoops(QMediaPlayer::Infinite);
}

// void Widget::track(Widget*& w)
// {
//     int x = rand()%(_MainW-(_width/2));
//     int y = rand()%(_MainH-(_height/2));
//     w->setGeometry(x,y,_width,_height);
// }
void Widget::track(Widget*& w)
{
    // 最远点采样：随机 10 个候选，取离已有窗口最远的
    QPoint best;
    double bestDist = -1;
    for (int i = 0; i < 10; i++) {
        QPoint c(rand() % qMax(1, _MainW - _width),
                 rand() % qMax(1, _MainH - _height));
        double d = 1e18;
        for (auto& p : _widgets)
            if (p) d = qMin(d, QLineF(c, p->pos()).length());
        if (d > bestDist) { bestDist = d; best = c; }
    }
    w->setGeometry(best.x(), best.y(), _width, _height);
}

Widget::~Widget()
{
    delete ui;
}
