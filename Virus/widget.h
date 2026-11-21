#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <list>
#include <QMediaPlayer>
#include <QAudioOutput>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr, bool isMainWindow = true, Widget* root = nullptr);
    //生成窗口
    void proWindow();

    //清理窗口
    void windowClear();

    //背景声设置
    void backGroundSound(QMediaPlayer*& player, QUrl url, float volume);

    //窗口生成轨迹
    void track(Widget*& w);

    ~Widget() override;

private:
    QTimer* _timer = nullptr;
    QTimer* _count = nullptr;
    int _timePasses = 0;

    int _MainW = 0;
    int _MainH = 0;

    int _width =350;
    int _height = 300;

    std::list<Widget*> _widgets;

    //声音
    QMediaPlayer *_block2_player = nullptr;
    QMediaPlayer *_block10_player = nullptr;
    QMediaPlayer *_clown_player1 = nullptr;
    QMediaPlayer *_clown_player2 = nullptr;
    QMediaPlayer *_clown_player3 = nullptr;

    int _spawnIdx = 0;

    Widget* _root = nullptr;

    Ui::Widget *ui;
};
#endif // WIDGET_H
