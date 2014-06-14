#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTableWidget>
#include "game.h"
#include "player.h"

namespace Ui {
class SetWindow;
}

class SetWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SetWindow(QWidget *parent = 0);
    ~SetWindow();

    Game &getGameRef();
    QTableWidget *getTableRef();


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
    QList<QTableWidgetItem> allItems;

    void tableManagement();
    //void setShipTable(int len);
    void refresh(int);
    void resqueBoard();
    void discon();


signals:
    void sendTable(QTableWidget *);
    void startGame();


public slots:
    void getName(QString);
    void selectSubmarine();
    void selectDestroyer();
    void selectBattleship();
    void selectAirCarrier();
    void getItems(QTableWidgetItem *item);
    void showItemList();
    void setPlayerShip();
    void changeDirection();
    void slotSendTable();
    void checkSet();

};

#endif // SETWINDOW_H
