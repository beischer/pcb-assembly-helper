#include "pcbviewscene.h"
#include <QDebug>
#include <QPoint>
#include <QPen>

PCBViewScene::PCBViewScene(QObject *parent) :
    QGraphicsScene(parent) {
}

void PCBViewScene::addMarker(QPointF pos) {
    MarkerItem *marker = new MarkerItem(this);
    marker->setMarker(pos);
    _markers.append(marker);
}

void PCBViewScene::clearMarkers() {
    for( int i=0; i<_markers.length(); i++ ) {
        _markers.at(i)->clearMarker();
        delete _markers.at(i);
    }
    _markers.clear();
}

QGraphicsItem *PCBViewScene::firstMarker() {
    if( _markers.length() > 0 ) {
        MarkerItem *marker = _markers.at(0);
        return marker->getMarkerItem();
    }
}

void PCBViewScene::loadImage(QString filename) {
    if( _viewImage.load(filename) ) {
        addPixmap(_viewImage);
        setSceneRect(_viewImage.rect());
    }

}
