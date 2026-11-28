#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QToolBar* tool1 = new QToolBar(this);
    QToolBar* tool2 = new QToolBar(this);
    tool1->addAction(new QAction("工具1"));
    tool1->addAction(new QAction("工具2"));
    tool2->addAction(new QAction("工具3"));

    this->addToolBar(Qt::LeftToolBarArea, tool1);
    this->addToolBar(tool2);
    tool2->setAllowedAreas(Qt::TopToolBarArea | Qt::RightToolBarArea);

    QIcon icon = QIcon(":/file.png");
    QAction* action1 = new QAction("打开文件");
    action1->setIcon(icon);
    tool1->addAction(action1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
