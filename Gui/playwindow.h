#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "game.h"
#include <QPainter>
#include "enddialog.h"

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PlayWindow(QTableWidget *table, Game _game, QWidget *parent = 0);
    ~PlayWindow();
    

private:
    Ui::PlayWindow *ui;
    Player player;
    Player enemy;
    Game game;
    Board &playerBoard;
    Board &enemyBoard;
    int sqSize;
    int width;
    int height;
    QTableWidget *playerTmp;
    QColor black, red;
    QPen pen;
    QPainter painter;
    EndDialog *end;

    void tableManagement();
    void setShips();


public slots:
    void setGameRef(Game &_game);
    void getStartActivity(bool);
    void setBomb(int a, int b);
    void getBomb(int r, int c);
};

#endif // PLAYWINDOW_H
