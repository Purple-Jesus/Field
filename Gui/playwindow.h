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

/**
 * @brief The PlayWindow class
 * this is the class for the Window where the game acctually happens
 * it contains two QTableWidgets which are use as boards the left is the board of the player
 * and on the left the enemy board is displayed to get bombed by the player
 */
class PlayWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PlayWindow(bool h, Game _game, QWidget *parent);
    ~PlayWindow();
    

private:
    Ui::PlayWindow *ui;
    //Player player;
    //Player enemy;
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
    bool host;
    QImage templatBlue;
    QImage templatBlack;
    int countOwn;
    int countOther;

    void tableManagement();
    void setShips();
    void countSet();

signals:
    void quitSignal();

private slots:
    void setBomb(int a, int b);
    void getBombed(int r, int c);

public slots:
    //void setGameRef(Game &_game);
    //void getStartActivity(bool);
    void revenge();
    //void quitGame();
};

#endif // PLAYWINDOW_H
