#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    //无限生成弹窗，在15个后加卡顿音效，加恶搞图片（动图，小丑（加小丑音），或呕吐）
    //调整生成位置
    //最后一步窗口最大化，调黑或者其他炸裂的颜色或动图，只能特殊快捷键才能关(Alt+q+Tab)

    return QApplication::exec();
}
