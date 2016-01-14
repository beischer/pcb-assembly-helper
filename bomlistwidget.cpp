#include "bomlistwidget.h"
#include <QDebug>
#include <QFileDialog>

BOMListWidget::BOMListWidget(QWidget *parent) :
    QWidget(parent)
{
    _searchBox = new QLineEdit("");
    _searchBox->setVisible(true);
    _layout.addWidget(_searchBox, 0, 0, 1, 2);


    _tableWidget = new QTableWidget();
    _tableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );
    _layout.addWidget(_tableWidget, 1, 0, 1, 2);

    _setRef1Button = new QPushButton("Set reference 1");
    _layout.addWidget(_setRef1Button, 2, 0, 1, 1);

    _setRef2Button = new QPushButton("Set reference 2");
    _layout.addWidget(_setRef2Button, 2, 1, 1, 1);

    _loadPositionFileButton = new QPushButton("Load position file");
    _layout.addWidget(_loadPositionFileButton, 3, 0, 1, 1);

    _loadBoardFileButton = new QPushButton("Load board file");
    _layout.addWidget(_loadBoardFileButton, 3, 1, 1, 1);

    _rotateView180Button = new QPushButton("Rotate view 180 degrees");
    _layout.addWidget(_rotateView180Button, 4, 0, 1, 1);

    setLayout(&_layout);

    setSearchFilter("");

    connect( _searchBox, SIGNAL(textChanged(QString)), SLOT(onSearchTextChange(QString)) );
    connect( _tableWidget, SIGNAL(itemSelectionChanged()), SLOT(onSelectionChange()) );
    connect( _setRef1Button, SIGNAL(clicked()), SLOT(onSetRef1ButtonClick()) );
    connect( _setRef2Button, SIGNAL(clicked()), SLOT(onSetRef2ButtonClick()) );
    connect( _loadPositionFileButton, SIGNAL(clicked()), SLOT(onLoadPositionFileButtonClick()) );
    connect( _loadBoardFileButton, SIGNAL(clicked()), SLOT(onLoadBoardfileButtonClick()) );
    connect( _rotateView180Button, SIGNAL(clicked()), SLOT(onRotateView180ButtonClick()) );
}

void BOMListWidget::setSearchFilter(QString search) {
    QList<BOMEntry> matches;
    if( search.isNull() ) {
        matches = _bom.all();
    }
    else {
        _bom.search(search);
        matches = _bom.matches();
    }

    _tableWidget->clear();
    _tableWidget->setRowCount( matches.length() );
    _tableWidget->setColumnCount(3);
    _tableWidget->hideColumn(0);

    for( int i=0; i<matches.length(); i++ ) {
        BOMEntry entry = matches.at(i);
        QString indexText;
        indexText.sprintf("%u", entry.index());
        QTableWidgetItem *col0 = new QTableWidgetItem( indexText );
        QTableWidgetItem *col1 = new QTableWidgetItem(entry.designator());
        QTableWidgetItem *col2 = new QTableWidgetItem(entry.partNumber());
        col0->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        col1->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        col2->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        _tableWidget->setItem(i, 0, col0);
        _tableWidget->setItem(i, 1, col1);
        _tableWidget->setItem(i, 2, col2);
        if( matches.length() == 1 ) {
            col1->setSelected(true);
        }
    }

    QStringList headers;
    headers.append("");
    headers.append("Designator");
    headers.append("Part Number");
    _tableWidget->setHorizontalHeaderLabels( headers );

}

void BOMListWidget::onSearchTextChange(QString text) {
    setSearchFilter(text);
}

void BOMListWidget::onSelectionChange() {
    QList<BOMEntry> selectedEntries;
    for( int i=0; i<_tableWidget->rowCount(); i++ ) {
        if( _tableWidget->item(i,1)->isSelected() ) {
            int index = _tableWidget->item(i,0)->text().toInt();
            selectedEntries.append( _bom.bomEntryByIndex(index) );
        }
    }
    if( selectedEntries.isEmpty() == false ) {
        emit( sigComponentsSelected(selectedEntries) );
    }
}

void BOMListWidget::onSetRef1ButtonClick() {
    QList<BOMEntry> selectedEntries;
    for( int i=0; i<_tableWidget->rowCount(); i++ ) {
        if( _tableWidget->item(i,1)->isSelected() ) {
            int index = _tableWidget->item(i,0)->text().toInt();
            selectedEntries.append( _bom.bomEntryByIndex(index) );
        }
    }
    if( selectedEntries.length() == 1 ) {
        BOMEntry selected = selectedEntries.at(0);
        emit( sigSetRefPoint(0, selected.position()) );
    }
}

void BOMListWidget::onSetRef2ButtonClick() {
    QList<BOMEntry> selectedEntries;
    for( int i=0; i<_tableWidget->rowCount(); i++ ) {
        if( _tableWidget->item(i,1)->isSelected() ) {
            int index = _tableWidget->item(i,0)->text().toInt();
            selectedEntries.append( _bom.bomEntryByIndex(index) );
        }
    }
    if( selectedEntries.length() == 1 ) {
        BOMEntry selected = selectedEntries.at(0);
        emit( sigSetRefPoint(1, selected.position()) );
    }
}

void BOMListWidget::onLoadPositionFileButtonClick() {
    QString filters("Position files (*.pos)");
    QString filename = QFileDialog::getOpenFileName(this, "Load position file", "", filters);
    if( !filename.isNull() ) {
        _bom.loadBOM(filename);
    }
    setSearchFilter("");
}

void BOMListWidget::onLoadBoardfileButtonClick() {
    emit(sigLoadBoardFileButtonClicked());
}

void BOMListWidget::onRotateView180ButtonClick() {
    emit( sigRotateView180() );
}
