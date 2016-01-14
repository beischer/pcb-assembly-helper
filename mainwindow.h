#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pcbviewscene.h"
#include "pcbview.h"
#include "bomlistwidget.h"

#include <QMainWindow>
#include <QGridLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PCBViewScene *zoomViewScene;
    QPixmap largeViewImage, zoomViewImage;

    PCBView *zoomView;
    BOMListWidget _BOMList;
    QGridLayout _layout;

private slots:
//    void onClickInOverview(int button, QPointF p);
//    void onScrollInOverview(int delta, QPointF pos);

};

#endif // MAINWINDOW_H
