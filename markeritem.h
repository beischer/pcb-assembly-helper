#ifndef MARKERITEM_H
#define MARKERITEM_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

class MarkerItem
{
private:
    QGraphicsLineItem *_markerLine1, *_markerLine2;
    QGraphicsItem *_markerCenter;
public:
    MarkerItem(QGraphicsScene *scene);
    ~MarkerItem();
    void setMarker( QPointF pos );
    void clearMarker();
    QGraphicsItem *getMarkerItem();
};

#endif // MARKERITEM_H
