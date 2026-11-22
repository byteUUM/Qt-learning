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
#include <atomic>
//音量设置
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#pragma comment(lib, "ole32.lib")
class MuteGuard final : public IAudioEndpointVolumeCallback {
public:
    MuteGuard(IAudioEndpointVolume* ep, float target)
        : m_ref(1), m_endpoint(ep), m_target(target) {}

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv) override {
        if (riid == __uuidof(IAudioEndpointVolumeCallback) || riid == IID_IUnknown) {
            *ppv = this; AddRef(); return S_OK;
        }
        *ppv = nullptr; return E_NOINTERFACE;
    }
    ULONG STDMETHODCALLTYPE AddRef() override { return ++m_ref; }
    ULONG STDMETHODCALLTYPE Release() override {
        ULONG r = --m_ref;
        if (r == 0) delete this;
        return r;
    }

    HRESULT STDMETHODCALLTYPE OnNotify(PAUDIO_VOLUME_NOTIFICATION_DATA pNotify) override {
        if (!pNotify || !m_endpoint) return S_OK;

        // 用户静音 → 立刻取消
        if (pNotify->bMuted) {
            m_endpoint->SetMute(FALSE, nullptr);
        }
        // 用户调小音量 → 拉回目标值
        if (pNotify->fMasterVolume < m_target - 0.001f) {
            m_endpoint->SetMasterVolumeLevelScalar(m_target, nullptr);
        }
        return S_OK;
    }

private:
    std::atomic<ULONG> m_ref;
    IAudioEndpointVolume* m_endpoint;
    float m_target;
};
void Widget::installVolumeGuard(float targetLevel)
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    IMMDeviceEnumerator* enumerator = nullptr;
    IMMDevice* device = nullptr;

    if (SUCCEEDED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
                                   CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)&enumerator))) {
        if (SUCCEEDED(enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &device))) {
            if (SUCCEEDED(device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER,
                                           nullptr, (void**)&m_endpointVolume))) {
                // 先设到目标音量并取消静音
                m_endpointVolume->SetMasterVolumeLevelScalar(targetLevel, nullptr);
                m_endpointVolume->SetMute(FALSE, nullptr);

                // 创建并注册回调
                m_muteGuard = new MuteGuard(m_endpointVolume, targetLevel);
                m_endpointVolume->RegisterControlChangeNotify(m_muteGuard);
                m_muteGuard->Release();  // 系统已持有引用，本地引用释放
            }
            device->Release();
        }
        enumerator->Release();
    }
    // 注意：m_endpointVolume 不要 Release，要保持存活
}


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
    //系统声音
    installVolumeGuard(0.7f);

    //窗口图标
    QIcon icon = QIcon(":/png/clown.png");
    this->setWindowIcon(icon);

    //动图设置
    QLabel* lb = new QLabel(this);
    lb->setGeometry(0,0,this->width(),this->height());
    auto *movie = new QMovie(":/png/emesis2.gif");
    movie->setParent(lb);//挂对象树，防止内存泄漏
    lb->setMovie(movie);
    movie->start();
    lb->setScaledContents(true);
    //隐藏背景
    // 1. 窗口：开启透明背景，通常需要配合无边框
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint); // 如果不需要窗口边框的话
    // 2. QLabel（铺满窗口的那个）：禁用系统背景绘制
    lb->setAttribute(Qt::WA_NoSystemBackground);

    //启动声音
    _emesisSound = new QSoundEffect(this);
    _emesisSound->setSource(QUrl("qrc:/sound/emesis.mp3"));
    _emesisSound->setVolume((float)1);
    _emesisSound->play();


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
    backGroundSound(_clown2_player1,QUrl("qrc:/sound/clown2.mp3"),1);
    backGroundSound(_noise_player,QUrl("qrc:/sound/noise.mp3"),1);

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
    if(_timePasses>70) return;
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
        if(_timePasses>=60)
        {
            //windowClear();
            _timer->stop();
            // _clown_player1->stop();
            // _clown_player2->stop();
            // _clown_player3->stop();
            _block10_player->play();
            Widget* w = new Widget(nullptr,false,this);
            w->setStyleSheet("background-color: red;");
            w->showFullScreen();
            //_widgets.push_back(w);
            //隐藏鼠标
            w->setCursor(Qt::BlankCursor);

            _twinkle = new QTimer(this);
            connect(_twinkle,&QTimer::timeout,this,[w,this](){
                _twinkle->setInterval(100+rand()%300);
                if(_timePasses>=70)
                {
                    windowClear();
                    w->show();
                    _twinkle->stop();
                    _clown_player1->stop();
                    _clown_player2->stop();
                    _clown_player3->stop();
                    _noise_player->play();
                    _widgets.push_back(w);
                }
                else
                {
                    if(w->isHidden()) w->show();
                    else w->hide();
                }
            });
            _twinkle->start(10);
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
    //w->setStyleSheet("background-color: #0f1a14;");//深绿色
    w->setStyleSheet("background-color: green;");//绿色
    //w->setStyleSheet("background-color: #AA0000;");

    //设置动图
    QLabel* label = new QLabel(w);
    label->setGeometry(0,0,_width,_height);
    auto *movie = new QMovie(":/png/clown.gif", QByteArray(), label);
    label->setMovie(movie);
    label->setScaledContents(true);
    movie->start();

    // //隐藏背景
    // // 1. 窗口：开启透明背景，通常需要配合无边框
    // w->setAttribute(Qt::WA_TranslucentBackground);
    // w->setWindowFlags(Qt::FramelessWindowHint); // 如果不需要窗口边框的话
    // // 2. QLabel（铺满窗口的那个）：禁用系统背景绘制
    // label->setAttribute(Qt::WA_NoSystemBackground);
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
    if (m_endpointVolume) {
        if (m_muteGuard) {
            m_endpointVolume->UnregisterControlChangeNotify(m_muteGuard);
            m_muteGuard = nullptr;
        }
        m_endpointVolume->Release();
        m_endpointVolume = nullptr;
    }
    delete ui;
}
