#include "bom.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

BOM::BOM() {
}

bool BOM::loadBOM(QString filename) {
    QFile bomFile;
    bomFile.setFileName(filename);
    if( bomFile.open(  QIODevice::ReadOnly ) == false ) {
        return false;
    }

    QTextStream textStream(&bomFile);
    QString line;

    int currentIndex = 0;

    _bomList.clear();
    do {
        line = textStream.readLine();
        line = line.trimmed();
        //       QRegularExpression regExp("^([^#]+?)(?: +)([\\w\\/]+)");
        QRegularExpression regExp("^([^#]+?)(?: +)([\\w\\/]+)(?: +)([\\w-\\/]+?)(?: +)([\\d-]+.\\d+)(?: +)([\\d-]+.\\d+)(?: +)(?: +)([\\d-]+.\\d+)(?: +)");
        QRegularExpressionMatch matches = regExp.match(line);
        QStringList matchList = matches.capturedTexts();
        if( matchList.length() > 4 ) {
            QString designator = matchList.at(1).trimmed();
            QString partNumber = matchList.at(2).trimmed();
            QString package = matchList.at(3).trimmed();
            float xpos = matchList.at(4).trimmed().toFloat();
            float ypos = matchList.at(5).trimmed().toFloat();
            float rotation = matchList.at(6).trimmed().toFloat();
            BOMEntry newEntry( currentIndex++, designator, partNumber, package, QPointF(xpos, ypos), rotation, true );
            _bomList.append(newEntry);
        }
    } while( line.isNull() == false );
    return true;
}

bool BOM::search(QString search) {
    _matches.clear();
    for( int i=0; i<_bomList.length(); i++ ) {
        BOMEntry entry = _bomList.at(i);
        if( entry.matchSearchString(search) ) {
            _matches.append(entry);
        }
    }
    return true;
}

QList<BOMEntry> &BOM::matches() {
    return _matches;
}

QList<BOMEntry> &BOM::all() {
    return _bomList;
}

BOMEntry BOM::bomEntryByIndex(int index) {
    if( index < _bomList.length() ) {
        return _bomList.at(index);
    }
}

