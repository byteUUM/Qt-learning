#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //获取或创建菜单栏
    QMenuBar* menuBar = this->menuBar();

    //创建并添加菜单
    QMenu* menu1 = new QMenu("文件(&F)");
    QMenu* menu2 = new QMenu("编辑(&E)");
    QMenu* menu3 = new QMenu("选择(&S)");
    QMenu* menu4 = new QMenu("查看(&V)");
    menuBar->addMenu(menu1);
    menuBar->addMenu(menu2);
    menuBar->addMenu(menu3);
    menuBar->addMenu(menu4);

    //创建并添加菜单项
    QAction* action1 = new QAction("新建(&N)");
    QAction* action2 = new QAction("打开(&O)");
    QAction* action3 = new QAction("保存");
    menu1->addAction(action1);
    menu1->addSeparator();
    menu1->addAction(action2);
    menu1->addSeparator();
    menu1->addAction(action3);

    QMenu* menu5 = new QMenu("菜单");
    QMenu* menu6 = new QMenu("子菜单");
    QAction* action4 = new QAction("项目1");
    QAction* action5 = new QAction("项目2");

    menuBar->addMenu(menu5);
    menu5->addMenu(menu6);
    menu6->addAction(action4);
    menu6->addAction(action5);

    QIcon icon1 = QIcon(":/png/file.png");
    QIcon icon2 = QIcon(":/png/new.png");

    menu1->setIcon(icon1);
    action1->setIcon(icon2);

}

MainWindow::~MainWindow()
{
    delete ui;
}
