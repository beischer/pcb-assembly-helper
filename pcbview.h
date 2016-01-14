#ifndef PCBVIEW_H
#define PCBVIEW_H

#include "pcbviewscene.h"
#include "bom.h"
#include "boardlayer.h"

#include <QGraphicsView>
#include <QWheelEvent>
#include <QPointF>
#include <QPushButton>

class PCBView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PCBView(QWidget *parent = 0);

private:
    PCBViewScene *_scene;
    QPointF _panStart;
    bool _pan;
    QPushButton *_button1;
    QPointF _refPointsScene[2];
    QPointF _refPointsComponent[2];
    QPointF _lastClickPos;

    QPointF mapComponentToScene(QPointF pos);
    BoardLayer *_silkLayer;
    BoardLayer *_copperLayer;

signals:
    
public slots:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void onComponentsSelected(QList<BOMEntry> selectedEntries);
    void onSetRefPoint(int index, QPointF pos);
    void onLoadBoardFile();
    void onRotateView180();
};

#endif // PCBVIEW_H
