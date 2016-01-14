#include "bomentry.h"
#include <QDebug>

BOMEntry::BOMEntry( int index, QString designator, QString partNumber, QString package, QPointF position, float rotation, bool mounted ) {
    _index = index;
    _designator = designator;
    _partNumber = partNumber;
    _package = package;
    _position = position;
    _rotation = rotation;
    _mounted = mounted;
}

int BOMEntry::index() {
    return _index;
}

QString BOMEntry::designator() {
    return _designator;
}

QString BOMEntry::partNumber() {
    return _partNumber;
}

QString BOMEntry::package() {
    return _package;
}

QPointF BOMEntry::position() {
    return _position;
}

float BOMEntry::rotation() {
    return _rotation;
}

bool BOMEntry::mounted() {
    return _mounted;
}

bool BOMEntry::assembled() {
    return _assembled;
}

void BOMEntry::setDesignator(QString designator) {
    _designator = designator;
}

void BOMEntry::setPartNumber(QString partNumber) {
    _partNumber = partNumber;
}

void BOMEntry::setPackage(QString package) {
    _package = package;
}

void BOMEntry::setPosition(QPointF position) {
    _position = position;
}

void BOMEntry::setRotation(float rotation) {
    _rotation = rotation;
}

void BOMEntry::setMounted(bool mounted) {
    _mounted = mounted;
}

void BOMEntry::setAssembled(bool assembled) {
    _assembled = assembled;
}

bool BOMEntry::matchSearchString(QString search ) {
    if( (_designator.append(" ").contains( search, Qt::CaseInsensitive ) ) || (_partNumber.append(" ").contains( search, Qt::CaseInsensitive ) ) ) {
        return true;
    }
    else {
        return false;
    }
}
