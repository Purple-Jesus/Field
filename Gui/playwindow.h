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
    explicit PlayWindow(Game _game, QWidget *parent);
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
    EndDialog *endD;

    void tableManagement();
    void setShips();

signals:
    void quitSignal();

public slots:
    //void setGameRef(Game &_game);
    void getStartActivity(bool);
    void setBomb(int a, int b);
    void getBombed(int r, int c);
    void revenge();
    void quitGame();
};

#endif // PLAYWINDOW_H
