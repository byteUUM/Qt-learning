#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // QPixmap pix = QPixmap(":/clown.png");
    // ui->label->setPixmap(pix);
    // //让label填充满整个窗口
    // ui->label->setGeometry(0,0,this->width(),this->height());
    // //自动拉伸，让图片填充满整个label
    // ui->label->setScaledContents(true);
    ui->label->setText("这是一段文本");
    ui->label->setAlignment(Qt::Alignment);

}

void Widget::resizeEvent(QResizeEvent * it)
{
    (void)it;
    ui->label->setGeometry(0,0,this->width(),this->height());
}

Widget::~Widget()
{
    delete ui;
}
