#include "widget.h"
#include "ui_widget.h"
#include <QShortcut>
#include <QLabel>
#include <QMovie>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QShortcut* sc = new QShortcut(this);
    sc->setKey(QKeySequence("Ctrl+Alt+K"));
    connect(sc,&QShortcut::activated,this,[=](){
        qApp->quit();
    });
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

    // 2. 你的 QLabel（铺满窗口的那个）：禁用系统背景绘制
    lb->setAttribute(Qt::WA_NoSystemBackground);

    // _timer = new QTimer(this);
    // connect(_timer,&QTimer::timeout,this,[=](){
    //     if(this->isHidden())
    //     {
    //         this->show();
    //         this->setStyleSheet("background-color:red");
    //     }
    //     else
    //     {
    //         this->hide();
    //         this->setStyleSheet("background-color:black");
    //     }
    // });
    // _timer->start(100);
}

Widget::~Widget()
{
    delete ui;
}
