#include "pcbviewscene.h"
#include "pcbview.h"
#include <QDebug>
#include <QScrollBar>
#include <QGraphicsItem>
#include <QFileDialog>

#include <QGraphicsSvgItem>
#include <QSvgRenderer>

PCBView::PCBView(QWidget *parent) :
    QGraphicsView(parent) {
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setDragMode(QGraphicsView::NoDrag);

    _scene = new PCBViewScene(parent);
    _scene->setBackgroundBrush( QBrush(Qt::black, Qt::SolidPattern) );
    setScene(_scene);

    _pan = false;
    _silkLayer = new BoardLayer();
    _copperLayer = new BoardLayer();

    PCBViewScene *_scene = (PCBViewScene*)scene();
    _scene->setBackgroundBrush( QBrush(Qt::black, Qt::SolidPattern) );
    //    setInteractive(false);
}

QPointF PCBView::mapComponentToScene(QPointF pos) {
    float w0 = _refPointsScene[0].x();
    float u0 = _refPointsScene[0].y();
    float w1 = _refPointsScene[1].x();
    float u1 = _refPointsScene[1].y();
    float x0 = _refPointsComponent[0].x();
    float y0 = _refPointsComponent[0].y();
    float x1 = _refPointsComponent[1].x();
    float y1 = _refPointsComponent[1].y();
    float kx = (w1-w0)/(x1-x0);
    float ky = (u1-u0)/(y1-y0);
    float x = pos.x();
    float y = pos.y();

    float w = w0 + (x - x0)*kx;
    float u = u0 + (y - y0)*ky;

    return QPointF(w, u);
}

void PCBView::wheelEvent(QWheelEvent *event) {
    float zoomFactor = 1.20f;
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if( event->delta() > 0 ) {
        scale(zoomFactor, zoomFactor);
    }
    else {
        scale(1/zoomFactor,1/zoomFactor);
    }
}

void PCBView::mousePressEvent(QMouseEvent *event) {
    if( event->button() == Qt::RightButton ) {
        _pan = true;
        _panStart = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    else if( event->button() == Qt::LeftButton ) {
        _scene->clearMarkers();
        QPoint clickPos = event->pos();
        QPointF scenePos = mapToScene( clickPos );
        _scene->addMarker(scenePos);
        _lastClickPos = scenePos;
    }
}

void PCBView::mouseReleaseEvent(QMouseEvent *event) {
    if( event->button() == Qt::RightButton ) {
        _pan = false;
        setCursor(Qt::ArrowCursor);
    }
}

void PCBView::mouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);
    if (_pan) {
        setTransformationAnchor(QGraphicsView::NoAnchor);
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - _panStart.x()) );
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - _panStart.y()));
        _panStart = event->pos();
    }
}

void PCBView::paintEvent(QPaintEvent *event) {
    QGraphicsView::paintEvent(event);
}

void PCBView::onComponentsSelected(QList<BOMEntry> selectedEntries) {
    if( _refPointsScene[0].isNull() || _refPointsScene[1].isNull() ) {
        return;
    }
    _scene->clearMarkers();
    float xmin, xmax, ymin, ymax;
    for( int i=0; i<selectedEntries.length(); i++ ) {
        BOMEntry _entry = selectedEntries.at(i);
        QPointF compPos = _entry.position();
        QPointF scenePos = mapComponentToScene(compPos);
        _scene->addMarker(scenePos);
        if( i==0 ) {
            xmin = scenePos.x();
            xmax = scenePos.x();
            ymin = scenePos.y();
            ymax = scenePos.y();
        }
        else {
            if( scenePos.x() > xmax ) xmax = scenePos.x();
            if( scenePos.x() < xmin ) xmin = scenePos.x();
            if( scenePos.y() > ymax ) ymax = scenePos.y();
            if( scenePos.y() < ymin ) ymin = scenePos.y();
        }
        if( selectedEntries.length() == 1 ) {
            ensureVisible( _scene->firstMarker(), 150, 150 );
        }
        else {
            fitInView( xmin-75, ymin-75, 150+xmax-xmin, 150+ymax-ymin, Qt::KeepAspectRatio );
        }
    }
}

void PCBView::onSetRefPoint(int index, QPointF pos) {
    if( (index == 0 || index == 1) && !_lastClickPos.isNull() ) {
        _refPointsScene[index] = _lastClickPos;
        _refPointsComponent[index] = pos;
        qDebug() << "Set reference" << index;
        qDebug() << "Scene position:" << _lastClickPos;
        qDebug() << "BOM position:" << pos;
    }
}

void PCBView::onLoadBoardFile() {
    QString filters("SVG files (*.svg)");
    QString silkFilename = QFileDialog::getOpenFileName(this, "Load silkscreen file", "", filters);
    QString copperFilename = QFileDialog::getOpenFileName(this, "Load copper file", "", filters);
    if( !copperFilename.isNull() ) {
        _copperLayer->loadSvg(copperFilename);
        _copperLayer->setColor(QColor(255,0,0));
        _scene->addItem(_copperLayer->pixmapItem);
    }
    if( !silkFilename.isNull() ) {
        _silkLayer->loadSvg(silkFilename);
        _silkLayer->setColor(QColor(0,255,0));
        _scene->addItem(_silkLayer->pixmapItem);
    }
}

void PCBView::onRotateView180() {
    rotate(180.0);
}

