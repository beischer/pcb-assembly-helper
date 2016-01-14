#ifndef BOM_H
#define BOM_H

#include <QList>
#include <bomentry.h>

class BOM
{
public:
    BOM();
    //void addEntry( BOMEntry & entry );
    bool loadBOM( QString filename );
    bool search( QString search );
    QList<BOMEntry> & matches();
    QList<BOMEntry> &all();
    BOMEntry bomEntryByIndex(int index);

private:
    QList<BOMEntry> _bomList;
    QList<BOMEntry> _matches;
};

#endif // BOM_H
