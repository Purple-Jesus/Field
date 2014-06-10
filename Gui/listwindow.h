#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ListWindow;
}

class ListWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ListWindow(QWidget *parent);
    ~ListWindow();
    QString getIP();
    
private:
    Ui::ListWindow *ui;
    QString ip;

public slots:
    void startClicked();
    void setIP(QString i);

};

#endif // LISTWINDOW_H
