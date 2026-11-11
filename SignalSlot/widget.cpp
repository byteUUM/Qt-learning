#include "widget.h"
#include "ui_widget.h"
#include "QPushButton"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // QPushButton* button = new QPushButton(this);
    // button->setText("close");
    // button->move(300,300);
    // connect(button,&QPushButton::clicked,this,&Widget::close);
    //connect(const Qobject *sender,
    //        const char * signal
    //        const Q0bject * receiver
    //        const char * method
    //        Qt::ConnectionType type = Qt::AutoConnection
    //)
    // QPushButton* button = new QPushButton(this);
    // button->setText("Button");
    // connect(button,&QPushButton::clicked, this, &Widget::handButton);
    connect(this,&Widget::mySignal,this,&Widget::handleMySignal);

    srand(time(NULL));
    QPushButton* bt = new QPushButton(this);
    int x = this->width() - bt->width();
    int y = this->height() - bt->height();
    bt->setText("别点我！");
    bt->move(rand()%x,rand()%y);
    connect(bt, &QPushButton::clicked, this, &Widget::handButton);
    connect(bt, &QPushButton::clicked, this, [=](){
        bt->move(rand()%x,rand()%y);
    });
}

void Widget::handleMySignal(const QString& str)//左值带const时可以绑定右值
{
    this->setWindowTitle(str);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::handButton()
{
    _count++;
    this->setWindowTitle("你已经按下"+QString::number(_count) +"次");
    //this->setWindowTitle("按钮已按下");
}

void Widget::on_pushButton_clicked()
{
    //emit mySignal();
    //this->setWindowTitle("on_pushButton_clicked");
}


void Widget::on_pushButton_2_clicked()
{
    emit mySignal("Button2","");
}


void Widget::on_pushButton_3_clicked()
{
    disconnect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::on_pushButton_2_clicked);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::handButton);
    emit mySignal("Button1","");
}

