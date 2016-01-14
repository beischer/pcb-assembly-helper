#ifndef BOMLISTWIDGET_H
#define BOMLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>

#include "bom.h"

class BOMListWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout _layout;
    QTableWidget *_tableWidget;
    QLineEdit *_searchBox;
    BOM _bom;
    QPushButton *_setRef1Button;
    QPushButton *_setRef2Button;
    QPushButton *_loadPositionFileButton;
    QPushButton *_loadBoardFileButton;
    QPushButton *_rotateView180Button;

public:
    explicit BOMListWidget(QWidget *parent = 0);
    void setSearchFilter( QString search );
    
signals:
    void sigComponentsSelected( QList<BOMEntry> selectedEntries );
    void sigSetRefPoint(int index, QPointF pos);
    void sigLoadBoardFileButtonClicked();
    void sigRotateView180();

public slots:
    void onSearchTextChange( QString text );
    void onSelectionChange();
    void onSetRef1ButtonClick();
    void onSetRef2ButtonClick();
    void onLoadPositionFileButtonClick();
    void onLoadBoardfileButtonClick();
    void onRotateView180ButtonClick();
};

#endif // BOMLISTWIDGET_H
