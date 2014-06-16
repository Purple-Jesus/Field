/*
#ifndef SQUAREOCCUPIED_H
#define SQUAREOCCUPIED_H

class SquareOccupied : public QObject
{
    Q_OBJECT
private:
    SquareOccupied():QObject()
      {};
    ~SquareOccupied(){};
protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // SQUAREOCCUPIED_H


bool SquareOccupied::eventFilter(QObject *a_object, QEvent *a_event)
{
  bool result = false;
  if ((a_object == table->viewport()) && (a_event->type() == QEvent::Drop))
  {
     QDropEvent *p_drop_event = static_cast<QDropEvent *>(a_event);
     QPoint pos = p_drop_event->pos();
     QModelIndex new_index = uii->fieldTable->indexAt(pos);
     if (new_index.column() >= 8)
     {
       // Ignore drop event
       p_drop_event->setDropAction(Qt::IgnoreAction);
       p_drop_event->accept();
       return true;
     }
     else
     {
       // Allow drop
       return false;
     }

  }
  return QObject::eventFilter(a_object, a_event);
}
*/
