#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "game.h"
#include <QPainter>

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PlayWindow(Game _game, QWidget *parent = 0);
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

    void tableManagement();
    void setShips();

public slots:
    void setGameRef(Game &_game);
    void setTableRef(QTableWidget *table);
    void setBomb(int r, int c);
    void getBomb(int r, int c);
};

#endif // PLAYWINDOW_H
