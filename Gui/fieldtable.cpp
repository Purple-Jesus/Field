#include "fieldtable.h"


Fieldtable::Fieldtable(QWidget *parent) :
    QTableWidget(parent)
{

}

Fieldtable::~Fieldtable()
{

}

bool Fieldtable::dropMimeData (int row, int column, const QMimeData * data, Qt::DropAction action)
{
    return QTableWidget::dropMimeData (row, 0, data, action);
}
