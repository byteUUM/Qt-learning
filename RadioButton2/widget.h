#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup>

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
    ~Widget() override;

private slots:
    void on_radioButton_male_clicked(bool checked);

    void on_radioButton_male_released();

    void on_radioButton_male_pressed();

    void on_radioButton_male_toggled(bool checked);

    void on_pushButton_submit_clicked();

private:
    Ui::Widget *ui;
    QButtonGroup* group1;
    QButtonGroup* group2;
    QButtonGroup* group3;
};
#endif // WIDGET_H
