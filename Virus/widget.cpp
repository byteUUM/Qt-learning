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
    QPixmap pix = QPixmap(":/png/emesis.png");
    QLabel* lb = new QLabel(this);
    lb->setGeometry(0,0,this->width(),this->height());
    lb->setPixmap(pix);
    lb->setScaledContents(true);

    //窗口生成定时器
    _timer = new QTimer(this);
    connect(_timer,&QTimer::timeout,this,&Widget::proWindow);
    _timer->start(1000);

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

}

void Widget::proWindow()
{
    Widget* w = new Widget(nullptr,false,this);
    if(_timePasses==1) _clown_player1->play();
    if(_timePasses==4) _clown_player2->play();
    if(_timePasses==6) _clown_player3->play();
    if(_timePasses==60)
    {
        windowClear();
        _timer->stop();
        w->showFullScreen();
        _clown_player1->stop();
        _clown_player2->stop();
        _clown_player3->stop();
        _block10_player->play();
        w->setStyleSheet("background-color: blue;");
    }
    else
    {
        //窗口生成轨迹
        track2(w);

        //窗口图标
        QIcon icon = QIcon(":/png/emesis.png");
        w->setWindowIcon(icon);
        w->setWindowTitle("clown");

        //动图设置
        QLabel* label = new QLabel(w);
        label->setGeometry(0,0,_width,_height);
        auto *movie = new QMovie(":/png/clown.gif");
        movie->setParent(label);//挂对象树，防止内存泄漏
        label->setMovie(movie);
        movie->start();
        label->setScaledContents(true);

    }
    if(_timePasses==10) _timer->setInterval(500);
    if(_timePasses==20)
    {
        _timer->setInterval(200);
        _block2_player->play();
    }
    if(_timePasses>=20&&!_widgets.empty())
    {
        _widgets.front()->close();
        _widgets.pop_front();
    }
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

void Widget::track1(Widget*& w)
{
    int x = rand()%(_MainW-(_width/2));
    int y = rand()%(_MainH-(_height/2));
    w->setGeometry(x,y,_width,_height);
}
void Widget::track2(Widget*& w)
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

void Widget::track3(Widget*& w)
{
    int n = _spawnIdx++;
    double cx = (_MainW - _width)  / 2.0;   // 窗口左上角的中心基准
    double cy = (_MainH - _height) / 2.0;
    double ax = cx, ay = cy;                // 椭圆半轴，铺满屏幕
    int x, y;

    int ring = 0, cnt = 1, m = n;
    while (m >= cnt) { m -= cnt; ring++; cnt = 6 * ring; }  // 第 ring 圈 6*ring 个，六边形数
    double R = ring / 8.0;                                   // 8 圈铺满
    double theta = cnt > 1 ? 2 * M_PI * m / cnt : 0;
    x = cx + ax * R * std::cos(theta);
    y = cy + ay * R * std::sin(theta);

    w->setGeometry(x, y, _width, _height);
}


void Widget::track4(Widget*& w)
{
    int n = _spawnIdx++;
    double cx = (_MainW - _width)  / 2.0;   // 窗口左上角的中心基准
    double cy = (_MainH - _height) / 2.0;
    double ax = cx, ay = cy;                // 椭圆半轴，铺满屏幕
    int x, y;

    double t = n * 0.15;
    x = cx + ax * std::sin(3 * t + M_PI / 2);
    y = cy + ay * std::sin(2 * t);

    w->setGeometry(x, y, _width, _height);
}
void Widget::track5(Widget*& w)
{
    int n = _spawnIdx++;
    double cx = (_MainW - _width)  / 2.0;   // 窗口左上角的中心基准
    double cy = (_MainH - _height) / 2.0;
    double ax = cx, ay = cy;                // 椭圆半轴，铺满屏幕
    int x, y;

    double t = n * 0.25;
    double r = (t / 20.0);                  // 每圈半径增长恒定
    r = std::fmod(r, 1.0);                  // 超出后从中心重新开始
    x = cx + ax * r * std::cos(t);
    y = cy + ay * r * std::sin(t);

    w->setGeometry(x, y, _width, _height);
}
void Widget::track6(Widget*& w)
{
    int n = _spawnIdx++;
    double cx = (_MainW - _width)  / 2.0;   // 窗口左上角的中心基准
    double cy = (_MainH - _height) / 2.0;
    double ax = cx, ay = cy;                // 椭圆半轴，铺满屏幕
    int x, y;

    double t = n * 0.12;
    double k = 5;                           // 奇数 k 得 k 瓣，偶数 k 得 2k 瓣
    double r = std::cos(k * t);
    x = cx + ax * r * std::cos(t);
    y = cy + ay * r * std::sin(t);

    w->setGeometry(x, y, _width, _height);
}
void Widget::track7(Widget*& w)
{
    int n = _spawnIdx++;
    double cx = (_MainW - _width)  / 2.0;   // 窗口左上角的中心基准
    double cy = (_MainH - _height) / 2.0;
    double ax = cx, ay = cy;                // 椭圆半轴，铺满屏幕
    int x, y;

    double t = n * 0.15;
    x = cx + ax * std::sin(3 * t + M_PI / 2);
    y = cy + ay * std::sin(2 * t);

    w->setGeometry(x, y, _width, _height);
}



Widget::~Widget()
{
    delete ui;
}
