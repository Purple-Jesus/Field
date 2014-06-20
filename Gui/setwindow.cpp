#include "Gui/setwindow.h"
#include "ui_setwindow.h"
#include <QtTest/QTest>
#include <QDebug>
#include "my_headers.h"

// Replace this with the current ini. list to get real ships
//    left("images/left.png"), hmiddle("images/hmiddle.png"),right("images/right.png"),
//    top("images/top.png"), vmiddle("images/vmiddle.png"), bottom("images/bottom.png")
SetWindow::SetWindow(QWidget *parent) :
    QMainWindow(parent),
    uii(new Ui::SetWindow),
    left("images/white.png"), hmiddle("images/white.png"),right("images/white.png"),
    top("images/white.png"), vmiddle("images/white.png"), bottom("images/white.png")
{
    qDebug("    SetWindow");
    //oc = new SquareOccupied(this);
    sub=5;
    dest=4;
    batt=3;
    air=1;
    horizontal = true;
    width = 10;
    height = width;
    uii->setupUi(this);
    sqSize = 47;
    uii->shipTable->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    uii->statusbar->showMessage("Plazieren Sie Ihre Schiffe.");
    setWindowIcon(QPixmap("images/ship.png"));
    setWindowTitle("Ship Happens");
    tableManagement();
    std::string enemyN = "Ganzer Peter";
    std::string playerN = name.toStdString();
    game.change_player_name(playerN);
    game.change_enemy_name(enemyN);
    //playerBoard = game.getBoardRef();
    game.getBoardRef().clear_board();

    //uii->fieldTable->installEventFilter(eventFilter);

    //connect(uii->submarineButton, SIGNAL(clicked()), this, SLOT(setSubmarine()));
    connect(uii->fieldTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(getItems(QTableWidgetItem*)));
    connect(uii->destroyerButton, SIGNAL(clicked()), this, SLOT(selectDestroyer()));
    connect(uii->submarineButton, SIGNAL(pressed()), this, SLOT(selectSubmarine()));
    connect(uii->battleButton, SIGNAL(clicked()), this, SLOT(selectBattleship()));
    connect(uii->directionButton, SIGNAL(clicked()), this, SLOT(changeDirection()));
    //connect(uii->startButton, SIGNAL(clicked()), this, SLOT(slotSendTable()));
    connect(uii->startButton, SIGNAL(clicked()), this, SLOT(checkSet()));
    connect(this, SIGNAL(startGame()), parent, SLOT(startGame()));
    connect(uii->airCarrierButton, SIGNAL(clicked()), this, SLOT(selectAirCarrier()));
    connect(uii->shipTable, SIGNAL(cellPressed(int,int)), this, SLOT(resqueTable(int,int)));
    connect(uii->shipTable, SIGNAL(itemSelectionChanged()), this, SLOT(selectAll()));
}


SetWindow::~SetWindow()
{
    delete uii;
    qDebug("    ~SetWindow");

}

void SetWindow::resqueTable(int a, int b)
{
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            allIcons << uii->fieldTable->itemAt(i,j)->icon();
        }
    }
}

void SetWindow::checkSet()
{
    //if((sub == -1) && (dest == -1) && (batt == -1) && (air == -1))
    if(air == -1){
        qDebug("Hilfe");
        emit startGame();
        //game.player_print_boards();
    }
    else
        uii->statusbar->showMessage("Es müssen erst alle Schiffe plaziert werden.",5000);
}

/*
void SetWindow::slotSendTable()
{
    emit sendTable(uii->fieldTable);
}
*/

// Calls the place_ships function of the game-class
void SetWindow::setPlayerShip()
{
    Square *sq1, *sq2, *sq3, *sq4, *sq5;
    sq1 = game.getBoardRef().get_Square_ptr((size_t)itemList[0]->column()+1, (size_t)itemList[0]->row()+1);
    sq2 = game.getBoardRef().get_Square_ptr((size_t)itemList[1]->column()+1, (size_t)itemList[1]->row()+1);

    switch(zaehler){
        case 2:
            if(!game.place_ships(sq1,sq2)){
                uii->statusbar->showMessage("Hier kann das Schiff nicht setzen.",3000);
                //QTest::qSleep(100);
                disconnect(uii->fieldTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(getItems(QTableWidgetItem*)));
                for(int i=0;i<height;i++){
                    for(int j=0;j<width;j++){
                        uii->fieldTable->itemAt(i,j)->setIcon(allIcons[index[i][j]]);
                    }
                }
                QTableWidgetItem *item[2];
                for(int i=0;i<2;i++){
                    qDebug() << "hallo" << i;
                    if(field[itemList[i]->column()][itemList[i]->row()] == 1){
                        item[i] = new QTableWidgetItem(QIcon(QPixmap("images/white.png")),"");
                        uii->fieldTable->setItem(itemList[i]->column(),itemList[i]->row(),item[i]);
                    }
                    else{
                        item[i] = new QTableWidgetItem(QIcon(QPixmap("images/sea.png")),"");
                        uii->fieldTable->setItem(itemList[i]->column(),itemList[i]->row(),item[i]);
                    }
                }

                connect(uii->fieldTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(getItems(QTableWidgetItem*)));

            }
            else{
                game.getPlayer().get_Submarine_ref(sub).set_ship(sq1,sq2);
                field[itemList[0]->column()][itemList[0]->row()] = 1;
                field[itemList[1]->column()][itemList[1]->row()] = 1;
                sub -= 1;
                uii->submarineButton->setText("Submarine " + QString::number(sub) + "x");
            }
            break;
        case 3:
            sq3 = game.getBoardRef().get_Square_ptr((size_t)itemList[2]->column()+1, (size_t)itemList[2]->row()+1);
            if(!game.place_ships(sq1,sq2,sq3))
                uii->statusbar->showMessage("Hier koennen sie ihr Schiff nicht setzen.",3000);
            else{
                game.getPlayer().get_Destroyer_ref((size_t)dest).set_ship(sq1,sq2,sq3);
                if(game.getPlayer().get_Destroyer_ref((size_t)dest).get_ship_set())
                    uii->statusbar->showMessage("Zerstoerer gesetzt:",2000);
            }
            dest -= 1;
            break;
        case 4:
            sq3 = game.getBoardRef().get_Square_ptr((size_t)itemList[2]->column()+1, (size_t)itemList[2]->row()+1);
            sq4 = game.getBoardRef().get_Square_ptr((size_t)itemList[3]->column()+1, (size_t)itemList[3]->row()+1);
            if(!game.place_ships(sq1,sq2,sq3,sq4))
                uii->statusbar->showMessage("Hier koennen sie ihr Schiff nicht setzen.",3000);
            else
                game.getPlayer().get_BattleShip_ref(batt).set_ship(sq1,sq2,sq3,sq4);
            batt -= 1;
            break;
        case 5:
            sq3 = game.getBoardRef().get_Square_ptr((size_t)itemList[2]->column()+1, (size_t)itemList[2]->row()+1);
            sq4 = game.getBoardRef().get_Square_ptr((size_t)itemList[3]->column()+1, (size_t)itemList[3]->row()+1);
            sq5 = game.getBoardRef().get_Square_ptr((size_t)itemList[4]->column()+1, (size_t)itemList[4]->row()+1);
            if(!game.place_ships(sq1,sq2,sq3,sq4,sq5)){
                uii->statusbar->showMessage("Hier koennen sie ihr Schiff nicht setzen.",3000);
                for(int i=0;i<5;i++){
                    qDebug("    resea");
                    QTableWidgetItem *item = new QTableWidgetItem(QIcon("images/sea.png"),"",1000);
                    qDebug("    1");
                    uii->fieldTable->setItem(itemList[i]->column(),itemList[i]->row(),item);
                    qDebug("    2");
                }
            }
            else
                game.getPlayer().get_AirCarrier_ref(air).set_ship(sq1,sq2,sq3,sq4,sq5);
            air -= 1;
            break;
    }
    discon();
}

// Disables the ship-buttons if the max amount of the shiptype is set
void SetWindow::discon()
{
    if(sub == 0){
        uii->submarineButton->setEnabled(false);
        uii->shipTable->setColumnCount(0);
        uii->shipTable->setRowCount(0);
        sub = -1;
    }
    if(dest == 0){
        uii->destroyerButton->setEnabled(false);
        uii->shipTable->setColumnCount(0);
        uii->shipTable->setRowCount(0);
        dest = -1;
    }
    if(batt == 0){
        uii->battleButton->setEnabled(false);
        uii->shipTable->setColumnCount(0);
        uii->shipTable->setRowCount(0);
        batt = -1;
    }
    if(air == 0){
        uii->airCarrierButton->setEnabled(false);
        disconnect(this, SLOT(selectAirCarrier()));
        uii->shipTable->setColumnCount(0);
        uii->shipTable->setRowCount(0);
        air = -1;
    }
}


// Saves the items witch are changed trough the dropEvent
void SetWindow::getItems(QTableWidgetItem *item)
{
    itemList << item;
    //allItems << *item;
    //qDebug("Droped succesfull");
    if(itemList.size() >= zaehler){
       // qDebug("Size itemList: %d",itemList.size());
        showItemList();
        setPlayerShip();
        for(int i=0;i<itemList.size();i++){
        //    itemList[i]->setFlags(Qt::NoItemFlags);
        }
        itemList.clear();
    }
}

// Slot to get the name of the player from the startWindow
void SetWindow::getName(QString n)
{
    name = n;
    setWindowTitle("Ship Happens - " + name);
    //me.change_player_names(name.toStdString(), "Netzwerkname");
}

void SetWindow::changeDirection()
{
    if(uii->directionButton->text() == "Horizontal"){
        uii->directionButton->setText("Vertikal");
        horizontal = false;
    }
    else{
        uii->directionButton->setText("Horizontal");
        horizontal = true;
    }
    refresh(zaehler);
}

// Set the shipTable with an Air Carrier for draging it to the fieldTable
void SetWindow::selectSubmarine()
{

    zaehler = 2;
    //uii->label->setText("Zaehler = " + QString::number(zaehler));
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setRowHeight(0,sqSize);

        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(left),"");
        itemL->setSizeHint(QSize(1,1));
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(right),"");
        itemR->setSizeHint(QSize(10,10));
        uii->shipTable->setItem(0,1,itemR);
    }
    else{
        uii->shipTable->setColumnCount(1);
        uii->shipTable->setColumnWidth(0,sqSize);

        uii->shipTable->setRowCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setRowHeight(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(top),"");
        itemL->setSizeHint(QSize(1,1));
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(bottom),"");
        itemR->setSizeHint(QSize(10,10));
        uii->shipTable->setItem(1,0,itemR);
    }
    uii->shipTable->selectAll();
    uii->shipTable->setGeometry(QRect(0,0,sqSize,sqSize));
    uii->shipTable->setIconSize(QSize(sqSize,sqSize));
}

// Set the shipTable with an Destroyer for draging it to the fieldTable
void SetWindow::selectDestroyer()
{
    zaehler = 3;
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setRowHeight(0,sqSize);

        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(left),"");
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(hmiddle),"");
        uii->shipTable->setItem(0,1,itemM);
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(right),"");
        uii->shipTable->setItem(0,2,itemR);

        uii->shipTable->selectAll();
        uii->shipTable->setIconSize(QSize(sqSize,sqSize));
    }
    else{
        uii->shipTable->setColumnCount(1);
        uii->shipTable->setColumnWidth(0,sqSize);

        uii->shipTable->setRowCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setRowHeight(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(top),"");
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(vmiddle),"");
        uii->shipTable->setItem(0,1,itemM);
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(bottom),"");
        uii->shipTable->setItem(0,2,itemR);

        uii->shipTable->selectAll();
        uii->shipTable->setIconSize(QSize(sqSize,sqSize));
    }
}

// Set the shipTable with an Battleship for draging it to the fieldTable
void SetWindow::selectBattleship()
{
    zaehler = 4;
    int fieldSize = sqSize;
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setRowHeight(0,fieldSize);

        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,fieldSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(left),"");
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(hmiddle),"");
        QTableWidgetItem *itemM2 = new QTableWidgetItem(QIcon(hmiddle),"");
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(right),"");
        uii->shipTable->setItem(0,0,itemL);
        uii->shipTable->setItem(0,1,itemM);
        uii->shipTable->setItem(0,2,itemM2);
        uii->shipTable->setItem(0,3,itemR);

        uii->shipTable->selectAll();
        uii->shipTable->setIconSize(QSize(fieldSize,fieldSize));
    }
    else{
        uii->shipTable->setColumnCount(1);
        uii->shipTable->setColumnWidth(0,fieldSize);

        uii->shipTable->setRowCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setRowHeight(i,fieldSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(top),"");
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(vmiddle),"");
        QTableWidgetItem *itemM2 = new QTableWidgetItem(QIcon(vmiddle),"");
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(bottom),"");
        uii->shipTable->setItem(0,0,itemL);
        uii->shipTable->setItem(0,1,itemM);
        uii->shipTable->setItem(0,2,itemM2);
        uii->shipTable->setItem(0,3,itemR);

        uii->shipTable->selectAll();
        uii->shipTable->setIconSize(QSize(fieldSize,fieldSize));
    }
}

// Set the shipTable with an Air Carrier for draging it to the fieldTable
void SetWindow::selectAirCarrier()
{
    zaehler = 5;
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setRowHeight(0,sqSize);

        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(left),"");
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(hmiddle),"");
        QTableWidgetItem *itemM2 = new QTableWidgetItem(QIcon(hmiddle),"");
        QTableWidgetItem *itemM3 = new QTableWidgetItem(QIcon(hmiddle),"");
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(right),"");
        uii->shipTable->setItem(0,0,itemL);
        uii->shipTable->setItem(0,1,itemM);
        uii->shipTable->setItem(0,2,itemM2);
        uii->shipTable->setItem(0,3,itemM3);
        uii->shipTable->setItem(0,4,itemR);

        uii->shipTable->selectAll();
        uii->shipTable->setIconSize(QSize(sqSize,sqSize));
    }
    else{
        uii->shipTable->setColumnCount(1);
        uii->shipTable->setColumnWidth(0,sqSize);

        uii->shipTable->setRowCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setRowHeight(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(top),"");
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(vmiddle),"");
        QTableWidgetItem *itemM2 = new QTableWidgetItem(QIcon(vmiddle),"");
        QTableWidgetItem *itemM3 = new QTableWidgetItem(QIcon(vmiddle),"");
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(bottom),"");
        uii->shipTable->setItem(0,0,itemL);
        uii->shipTable->setItem(0,1,itemM);
        uii->shipTable->setItem(0,2,itemM2);
        uii->shipTable->setItem(0,3,itemM3);
        uii->shipTable->setItem(0,4,itemR);

        uii->shipTable->selectAll();
        uii->shipTable->setIconSize(QSize(sqSize,sqSize));
    }
}


// Set the size, headernames of the rows and columns and fills the fieldTable with sea-Items
void SetWindow::tableManagement()
{
    uii->fieldTable->setAcceptDrops(true);
    uii->fieldTable->setRowCount(width);
    uii->fieldTable->setColumnCount(height);
    // set the headernames of the rows and columns
    QStringList hlist, vlist;
    vlist<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"
        <<"14"<<"15"<<"16"<<"17"<<"18"<<"19"<<"20";
    hlist<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"
        <<"O"<<"P"<<"Q"<<"R"<<"S"<<"T";
    uii->fieldTable->setHorizontalHeaderLabels(hlist.mid(0,width));
    uii->fieldTable->setVerticalHeaderLabels(vlist.mid(0,height));

    // manage the size of the squares of the table
    for(int i=0;i<height;i++)
        uii->fieldTable->setColumnWidth(i,sqSize);
    for(int i=0;i<width;i++)
        uii->fieldTable->setRowHeight(i,sqSize);

    // fills the index[][] with the position of the Squareg in the label list
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            index[i][j] = width * i + j;
            field[i][j] = 0;
        }
    }

    // fills the fields of the table with squareg items
    QPixmap pixmap("images/sea.png");
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            QTableWidgetItem *item = new QTableWidgetItem(QIcon(pixmap)," ",1000);
            uii->fieldTable->setItem(i,j,item);
            uii->fieldTable->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));
        }
    }
    uii->fieldTable->setDragDropMode(QAbstractItemView::DropOnly);
    uii->fieldTable->setIconSize(QSize(sqSize,sqSize));

}

/**
 * @brief SetWindow::refresh
 * function so update the shipTable after changing the direction of a ship
 * @param len
 **/
void SetWindow::refresh(int len)
{
    switch(len){
        case 2: selectSubmarine();
        break;
        case 3: selectDestroyer();
        break;
        case 4: selectBattleship();
        break;
        case 5: selectAirCarrier();
        break;
    }
}


void SetWindow::showItemList()
{
    QString str;
    for(int i=0;i<itemList.count();i++){
        str += "(" + QString::number(itemList[i]->column()) + "," + QString::number(itemList[i]->row()) + ") - ";
    }
}


Game &SetWindow::getGameRef()
{
    return game;
}

QTableWidget* SetWindow::getTable()
{
    return uii->fieldTable;
}

void SetWindow::selectAll()
{
    int rows = uii->shipTable->rowCount();
    int columns = uii->shipTable->columnCount();
    uii->shipTable->setRangeSelected(QTableWidgetSelectionRange(0,0,rows,columns),true);
}
