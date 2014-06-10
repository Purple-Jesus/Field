#ifndef FIELDTABLE_H
#define FIELDTABLE_H

#include <QTableWidget>

namespace Ui {
class Fieldtable;
}

class Fieldtable : public QTableWidget
{
    Q_OBJECT

public:
    explicit Fieldtable(QWidget *parent = 0);
    ~Fieldtable();

private:
        bool dropMimeData (int row, int column, const QMimeData * data, Qt::DropAction action);

};

#endif // FIELDTABLE_H
