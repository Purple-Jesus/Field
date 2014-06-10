#include "Gui/setwindow.h"
#include "ui_setwindow.h"
#include <QtTest/QTest>
#include <QDebug>
#include "my_headers.h"

SetWindow::SetWindow(QWidget *parent) :
    QMainWindow(parent),
    uii(new Ui::SetWindow)
{
    qDebug("    SetWindow");
    sub=5;
    dest=4;
    batt=3;
    air=1;
    horizontal = true;
    sqSize = 45;
    width = 10;
    height = width;
    uii->setupUi(this);
    uii->statusbar->showMessage("Plazieren Sie Ihre Schiffe.");
    setWindowIcon(QPixmap("images/ship.png"));
    tableManagement();
    std::string enemyN = "Ganzer Peter";
    std::string playerN = name.toStdString();
    game.change_player_name(playerN);
    game.change_enemy_name(enemyN);
    playerBoard = game.getBoardRef();
    playerBoard.init_board();
    playerBoard.clear_board();

    //uii->shipTable->resize(6*width,6*height);

    //connect(uii->submarineButton, SIGNAL(clicked()), this, SLOT(setSubmarine()));
    connect(uii->fieldTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(getItems(QTableWidgetItem*)));
    connect(uii->destroyerButton, SIGNAL(clicked()), this, SLOT(selectDestroyer()));
    connect(uii->submarineButton, SIGNAL(pressed()), this, SLOT(selectSubmarine()));
    connect(uii->battleButton, SIGNAL(clicked()), this, SLOT(selectBattleship()));
    connect(uii->directionButton, SIGNAL(clicked()), this, SLOT(changeDirection()));
    connect(uii->startButton, SIGNAL(clicked()), this, SLOT(slotSendTable()));
    connect(uii->startButton, SIGNAL(clicked()), parent, SLOT(startGame()));
    connect(uii->airCarrierButton, SIGNAL(clicked()), this, SLOT(selectAirCarrier()));

}


SetWindow::~SetWindow()
{
    delete uii;
    qDebug("~SetWindow");

}

void SetWindow::slotSendTable()
{
    emit sendTable(uii->fieldTable);
}

// Calls the place_ships function of the game-class
void SetWindow::setPlayerShip()
{
    Square *sq1, *sq2, *sq3, *sq4, *sq5;
    sq1 = playerBoard.get_Square_ptr((size_t)itemList[0]->column(), (size_t)itemList[0]->row());
    sq2 = playerBoard.get_Square_ptr((size_t)itemList[1]->column(), (size_t)itemList[1]->row());

    switch(zaehler){
        case 2:
            if(!game.place_ships(sq1,sq2)){
                uii->statusbar->showMessage("Hier koennen sie ihr Schiff nicht setzen.",5000);
            }
            sub -= 1;
            break;
        case 3:
            sq3 = playerBoard.get_Square_ptr((size_t)itemList[2]->column(), (size_t)itemList[2]->row());
            if(!game.place_ships(sq1,sq2,sq3))
                uii->statusbar->showMessage("Hier koennen sie ihr Schiff nicht setzen.",5000);
            dest -= 1;
            break;
        case 4:
            sq3 = playerBoard.get_Square_ptr((size_t)itemList[2]->column(), (size_t)itemList[2]->row());
            sq4 = playerBoard.get_Square_ptr((size_t)itemList[3]->column(), (size_t)itemList[3]->row());
            if(!game.place_ships(sq1,sq2,sq3,sq4))
                uii->statusbar->showMessage("Hier koennen sie ihr Schiff nicht setzen.",5000);
            batt -= 1;
            break;
        case 5:
            sq3 = playerBoard.get_Square_ptr((size_t)itemList[2]->column(), (size_t)itemList[2]->row());
            sq4 = playerBoard.get_Square_ptr((size_t)itemList[3]->column(), (size_t)itemList[3]->row());
            sq5 = playerBoard.get_Square_ptr((size_t)itemList[4]->column(), (size_t)itemList[4]->row());
            if(!game.place_ships(sq1,sq2,sq3,sq4,sq5))
                uii->statusbar->showMessage("Hier koennen sie ihr Schiff nicht setzen.",5000);
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

void SetWindow::resqueBoard()
{
    QList<QTableWidgetItem> jk;
    uii->fieldTable->clear();
    QPixmap pixmap("images/sea.png");
    qDebug("Hallo meine lieben");
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            QTableWidgetItem *item = new QTableWidgetItem(QIcon(pixmap)," ",1000);
            uii->fieldTable->setItem(i,j,item);
            uii->fieldTable->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));
        }
    }
    uii->fieldTable->setIconSize(QSize(sqSize,sqSize));

    int a,b;
    for(int i=0;i<allItems.size();i++){
        a = allItems[i].column();
        b = allItems[i].row();
        //if(allItems[i])
        uii->fieldTable->setItem(a,b,&allItems[i]);
    }
}

// Saves the items witch are changed trough the dropEvent
void SetWindow::getItems(QTableWidgetItem *item)
{
    itemList << item;
    allItems << *item;
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
    uii->label->setText("Zaehler = " + QString::number(zaehler));
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setRowHeight(0,sqSize);

        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(QPixmap("images/left.png")),"");
        itemL->setSizeHint(QSize(1,1));
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(QPixmap("images/right.png")),"");
        itemR->setSizeHint(QSize(10,10));
        uii->shipTable->setItem(0,1,itemR);
    }
    else{
        uii->shipTable->setColumnCount(1);
        uii->shipTable->setColumnWidth(0,sqSize);

        uii->shipTable->setRowCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setRowHeight(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(QPixmap("images/top.png")),"");
        itemL->setSizeHint(QSize(1,1));
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(QPixmap("images/bottom.png")),"");
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
    uii->label->setText("Zaehler = " + QString::number(zaehler));
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setRowHeight(0,sqSize);

        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(QPixmap("images/left.png")),"");
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(QPixmap("images/hmiddle.png")),"");
        uii->shipTable->setItem(0,1,itemM);
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(QPixmap("images/right.png")),"");
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

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(QPixmap("images/top.png")),"");
        uii->shipTable->setItem(0,0,itemL);
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(QPixmap("images/vmiddle.png")),"");
        uii->shipTable->setItem(0,1,itemM);
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(QPixmap("images/bottom.png")),"");
        uii->shipTable->setItem(0,2,itemR);

        uii->shipTable->selectAll();
        uii->shipTable->setIconSize(QSize(sqSize,sqSize));
    }
}

// Set the shipTable with an Battleship for draging it to the fieldTable
void SetWindow::selectBattleship()
{
    zaehler = 4;
    uii->label->setText("Zaehler = " + QString::number(zaehler));
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setRowHeight(0,sqSize);

        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(QPixmap("images/left.png")),"");
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(QPixmap("images/hmiddle.png")),"");
        QTableWidgetItem *itemM2 = new QTableWidgetItem(QIcon(QPixmap("images/hmiddle.png")),"");
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(QPixmap("images/right.png")),"");
        uii->shipTable->setItem(0,0,itemL);
        uii->shipTable->setItem(0,1,itemM);
        uii->shipTable->setItem(0,2,itemM2);
        uii->shipTable->setItem(0,3,itemR);

        uii->shipTable->selectAll();
        uii->shipTable->setIconSize(QSize(sqSize,sqSize));
    }
    else{
        uii->shipTable->setColumnCount(1);
        uii->shipTable->setColumnWidth(0,sqSize);

        uii->shipTable->setRowCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setRowHeight(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(QPixmap("images/top.png")),"");
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(QPixmap("images/vmiddle.png")),"");
        QTableWidgetItem *itemM2 = new QTableWidgetItem(QIcon(QPixmap("images/vmiddle.png")),"");
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(QPixmap("images/bottom.png")),"");
        uii->shipTable->setItem(0,0,itemL);
        uii->shipTable->setItem(0,1,itemM);
        uii->shipTable->setItem(0,2,itemM2);
        uii->shipTable->setItem(0,3,itemR);

        uii->shipTable->selectAll();
        uii->shipTable->setIconSize(QSize(sqSize,sqSize));
    }
}

// Set the shipTable with an Air Carrier for draging it to the fieldTable
void SetWindow::selectAirCarrier()
{
    zaehler = 5;
    uii->label->setText("Zaehler = " + QString::number(zaehler));
    if(horizontal){
        uii->shipTable->setRowCount(1);
        uii->shipTable->setRowHeight(0,sqSize);

        uii->shipTable->setColumnCount(zaehler);
        for(int i=0;i<zaehler;i++)
            uii->shipTable->setColumnWidth(i,sqSize);

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(QPixmap("images/left.png")),"");
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(QPixmap("images/hmiddle.png")),"");
        QTableWidgetItem *itemM2 = new QTableWidgetItem(QIcon(QPixmap("images/hmiddle.png")),"");
        QTableWidgetItem *itemM3 = new QTableWidgetItem(QIcon(QPixmap("images/hmiddle.png")),"");
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(QPixmap("images/right.png")),"");
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

        QTableWidgetItem *itemL = new QTableWidgetItem(QIcon(QPixmap("images/top.png")),"");
        QTableWidgetItem *itemM = new QTableWidgetItem(QIcon(QPixmap("images/vmiddle.png")),"");
        QTableWidgetItem *itemM2 = new QTableWidgetItem(QIcon(QPixmap("images/vmiddle.png")),"");
        QTableWidgetItem *itemM3 = new QTableWidgetItem(QIcon(QPixmap("images/vmiddle.png")),"");
        QTableWidgetItem *itemR = new QTableWidgetItem(QIcon(QPixmap("images/bottom.png")),"");
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
    uii->fieldTable->setIconSize(QSize(sqSize+3,sqSize+3));
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
    uii->label->setText(str);
}


Game &SetWindow::getGameRef()
{
    return game;
}

QTableWidget* SetWindow::getTableRef()
{
    return uii->fieldTable;
}
