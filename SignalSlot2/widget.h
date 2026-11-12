#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void handleMySignal(const QString& str);
    ~Widget() override;

private slots:


    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

signals:
    void mySignal(const QString& str1,const QString& str2);
    //自定义信号本质就是函数，不用实现，系统会自动帮实现

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
