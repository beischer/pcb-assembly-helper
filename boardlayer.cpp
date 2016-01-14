#include "boardlayer.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QPixmap>

BoardLayer::BoardLayer() {
    _loaded = false;
}

bool BoardLayer::loadSvg(QString filename, QColor backgroundColor) {
    if( _loaded ) {
        delete pixmapItem;
    }
    QSvgRenderer renderer;
    renderer.load(filename);
//    QPixmap image("c:/temp/test.png");
    QPixmap image(renderer.defaultSize()*3);
    image.fill(backgroundColor);
    QPainter painter(&image);
    renderer.render(&painter);
    painter.setCompositionMode( QPainter::CompositionMode_SourceIn );
    painter.fillRect(image.rect(), QColor(0,255,0));
    painter.end();
    pixmapItem = new QGraphicsPixmapItem(image);

    _loaded = true;
    return true;
}

void BoardLayer::setColor(QColor color) {
    QPixmap image = pixmapItem->pixmap();
    QPainter painter(&image);
    painter.setCompositionMode( QPainter::CompositionMode_SourceIn );
    painter.fillRect(image.rect(), color);
    painter.end();
    pixmapItem->setPixmap(image);
}

void BoardLayer::setAbsoluteRotation( float angle ) {
    pixmapItem->setRotation(angle);
}
