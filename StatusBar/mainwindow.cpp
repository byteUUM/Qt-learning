#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStatusBar* statusBar = this->statusBar();
    this->setStatusBar(statusBar);

    // //显示一个消息，3秒后消失
    // statusBar->showMessage("这是一条消息", 3000);

    //或者添加一个子控件,上面的临时显示会把下面控件遮挡
    // statusBar->addWidget(new QLabel("这是一条label"),1);
    // statusBar->addWidget(new QLabel("这是一条label"),2);

    //添加进度条控件
    QProgressBar* progressBar = new QProgressBar();
    progressBar->setRange(0,100);
    progressBar->setValue(0);
    statusBar->addWidget(progressBar);

    //模拟进度条不规则加载
    srand(time(NULL));
    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        progressBar->setValue(progressBar->value()+1);
        timer->setInterval(10+rand()%300);
        if(progressBar->value()==progressBar->maximum())
            timer->stop();
    });
    timer->start(1000);

    QPushButton* button = new QPushButton("按钮");
    statusBar->addPermanentWidget(button);
}

MainWindow::~MainWindow()
{
    delete ui;
}
