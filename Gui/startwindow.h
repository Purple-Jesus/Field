#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "Gui/setwindow.h"
#include "Gui/listwindow.h"
#include "playwindow.h"
#include <QMainWindow>
#include <QString>
#include <QDebug>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit StartWindow(QWidget *parent = 0);
    ~StartWindow();
    
private:
    Ui::StartWindow *ui;

    QString name;
    ListWindow *listW;
    SetWindow *setW;
    PlayWindow *playW;
    bool host;

signals:
    void setStartActivity(bool);

public slots:
    void getName(QString n);
    void openGame();
    void joinGame();
    void listWindowClosed();
    void startGame();
    void revenge();
};

#endif // STARTWINDOW_H
