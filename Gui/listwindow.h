#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QMainWindow>
#include "mysocket.h"

namespace Ui {
class ListWindow;
}

class ListWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ListWindow(MySocket &s, QWidget *parent);
    ~ListWindow();
    QString getIP();
    
private:
    Ui::ListWindow *ui;
    QString ip;
    MySocket *socke;

signals:
    void connected();

public slots:
    void startClicked();
    void setIP(QString i);

};

#endif // LISTWINDOW_H
