#ifndef BOARDLAYER_H
#define BOARDLAYER_H

#include <QGraphicsPixmapItem>

class BoardLayer
{
public:
    BoardLayer();
    bool loadSvg(QString filename, QColor backgroundColor = Qt::transparent);
    void setColor( QColor color );
    void setAbsoluteRotation(float angle);

    QGraphicsPixmapItem *pixmapItem;
private:
    bool _loaded;

signals:

public slots:

};

#endif // BOARDLAYER_H
