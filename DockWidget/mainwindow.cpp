#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDockWidget* dockWidget = new QDockWidget();
    this->addDockWidget(Qt::LeftDockWidgetArea,dockWidget);
    dockWidget->setGeometry(this->x(),this->y(),this->width(),this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}
