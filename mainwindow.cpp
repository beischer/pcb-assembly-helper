#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pcbview.h"
#include "pcbviewscene.h"
#include <QDebug>

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    zoomView = new PCBView(this);

    _layout.addWidget(zoomView, 0, 0, 2, 1);
    _layout.addWidget(&_BOMList, 0, 1, 1, 1);
    _layout.setColumnMinimumWidth(1, 500);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(&_layout);
    this->setCentralWidget(centralWidget);

    connect(&_BOMList, SIGNAL(sigComponentsSelected(QList<BOMEntry>)), zoomView, SLOT(onComponentsSelected(QList<BOMEntry>)) );
    connect(&_BOMList, SIGNAL(sigSetRefPoint(int,QPointF)), zoomView, SLOT(onSetRefPoint(int,QPointF)) );
    connect(&_BOMList, SIGNAL(sigLoadBoardFileButtonClicked()), zoomView, SLOT(onLoadBoardFile()) );
    connect(&_BOMList, SIGNAL(sigRotateView180()), zoomView, SLOT(onRotateView180()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
