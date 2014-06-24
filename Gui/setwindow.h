#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QEvent>
#include <QTableWidget>
#include <QPixmap>
#include "game.h"
#include "player.h"

namespace Ui {
class SetWindow;
}

/**
 * @brief The SetWindow class
 * in this window the player can set his ships
 */
class SetWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SetWindow(QWidget *parent = 0);
    ~SetWindow();

    Game &getGameRef();
    QTableWidget *getTable();
    //void clearTable();
    void setHost(bool h);


private:
    Ui::SetWindow *uii;

    Player player;
    Game game;
    Board playerBoard;
    QString name;
    int width;					// width of the field
    int height;					// height of the field
    int sqSize;					// The size of a square
    int index[10][10];
    int zaehler;                // Variable to count down if all coordinates are set
    int sub;
    int dest;
    int batt;
    int air;
    bool horizontal;
    QList<Square*> square;
    QList<QTableWidgetItem*> itemList;
    QList<QIcon> allIcons;
    QTableWidget rTable;
    QPixmap left;
    QPixmap hmiddle;
    QPixmap right;
    QPixmap top;
    QPixmap vmiddle;
    QPixmap bottom;
    int field[10][10];
    bool host;
    bool occupied;
    //SquareOccupied *oc;

    void tableManagement();
    void refresh(int);
    //void discon();


signals:
    //void sendTable(QTableWidget *);
    void startGame();

public slots:


private slots:
    void getEnemyName(QString);
    void selectSubmarine();
    void selectDestroyer();
    void selectBattleship();
    void selectAirCarrier();
    void getItems(QTableWidgetItem *item);
    //void showItemList();
    void setPlayerShip();
    void changeDirection();
    void checkSet();
    //void resqueTable(int a, int b);


};

#endif // SETWINDOW_H
