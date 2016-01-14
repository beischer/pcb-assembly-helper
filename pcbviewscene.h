#ifndef PCBVIEWSCENE_H
#define PCBVIEWSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QList>
#include <QPixmap>
#include <QDebug>

#include <markeritem.h>

class PCBViewScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PCBViewScene(QObject *parent = 0);
    void addMarker( QPointF pos );
    void clearMarkers();
    QGraphicsItem *firstMarker();
    void loadImage(QString filename);
    
private:
    QList<MarkerItem*> _markers;
    QPixmap _viewImage;

signals:
    void sigClick(int button, QPointF p);
    void sigScroll(int delta, QPointF pos);

public slots:
};

#endif // PCBVIEWSCENE_H
