#ifndef BOMENTRY_H
#define BOMENTRY_H

#include <QString>
#include <QPointF>

class BOMEntry
{
public:
    BOMEntry( int index, QString designator, QString partNumber, QString package, QPointF position, float rotation, bool mounted );
    int index();
    QString designator();
    QString partNumber();
    QString package();
    QPointF position();
    float rotation();
    bool mounted();
    bool assembled();

    void setDesignator( QString designator );
    void setPartNumber( QString partNumber );
    void setPackage( QString package );
    void setPosition( QPointF position );
    void setRotation( float rotation );
    void setMounted( bool mounted );
    void setAssembled( bool assembled );

    bool matchSearchString( QString search );

private:
    int _index;
    QString _designator;
    QString _partNumber;
    QString _package;
    QPointF _position;
    float _rotation;
    bool _mounted;
    bool _assembled;
};

#endif // BOMENTRY_H
