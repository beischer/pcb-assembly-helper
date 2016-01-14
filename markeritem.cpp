#include "markeritem.h"

MarkerItem::MarkerItem(QGraphicsScene *scene) {
    QPen pen(Qt::SolidPattern, 4);
    pen.setColor( QColor(255,255,255,250) );
    _markerLine1 = scene->addLine(0,0,0,0,pen);
    _markerLine1->setZValue(1000);
    _markerLine1->setVisible(false);
    _markerLine2 = scene->addLine(0,0,0,0,pen);
    _markerLine2->setZValue(1000);
    _markerLine2->setVisible(false);

    _markerCenter = scene->addRect(0,0,1,1);
    _markerCenter->setVisible(false);
}

MarkerItem::~MarkerItem() {
    clearMarker();
    delete _markerLine1;
    delete _markerLine2;
    delete _markerCenter;
}

void MarkerItem::setMarker(QPointF pos) {
    _markerLine1->setLine( pos.x()-30, pos.y()-30, pos.x()+30, pos.y()+30 );
    _markerLine1->setVisible(true);
    _markerLine2->setLine( pos.x()+30, pos.y()-30, pos.x()-30, pos.y()+30 );
    _markerLine2->setVisible(true);
    _markerCenter->setPos(pos.x(),pos.y());
}

void MarkerItem::clearMarker() {
    _markerLine1->setVisible(false);
    _markerLine2->setVisible(false);
}

QGraphicsItem *MarkerItem::getMarkerItem() {
    return _markerCenter;
}
