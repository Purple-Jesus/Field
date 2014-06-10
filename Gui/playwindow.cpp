#include "playwindow.h"
#include "ui_playwindow.h"

PlayWindow::PlayWindow(Game _game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayWindow),
    game(_game),
    playerBoard(game.getBoardRef()),
    enemyBoard(game.getEnemyBoardRef()),
    black(QColor(0,0,0)), red(QColor(255,0,0))
{
    qDebug("    Playwindow");
    ui->setupUi(this);
    width = 10;
    height = 10;
    sqSize = 45;
    pen.setWidth(10);
    pen.setJoinStyle(Qt::RoundJoin);
    game.enemy_set_ship_test();
    tableManagement();
    connect(ui->enemyTable, SIGNAL(cellClicked(int,int)), this, SLOT(setBomb(int,int)));
    connect(ui->playerTable, SIGNAL(cellClicked(int,int)), this, SLOT(getBomb(int,int)));
}

PlayWindow::~PlayWindow()
{
    delete ui;
}

void PlayWindow::getBomb(int r, int c)
{
    if(playerBoard.get_Square_ptr((size_t)r,(size_t)c)->get_square_hit()){
        ui->statusbar->showMessage("Dieses Feld wurde schon bombardiert.");
        return;
    }
    if(game.getPlayerState()){
        ui->statusbar->showMessage("Der andere Spieler ist am Zug.");
        return;
    }
    int size = ui->enemyTable->iconSize().height();
    QImage temp("images/sea.png");
    if(playerBoard.get_Square_ptr((size_t)r,(size_t)c)->get_square_set()){
        pen.setColor(red);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2-0.5)),((size/2-0.5)));
        painter.end();
        ui->statusbar->showMessage("Yeaaaayyy das war der Gegner.");
        playerBoard.get_Square_ptr(r,c)->set_hit();
    }
    else{
        pen.setColor(black);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2)-0.5),((size/2)-0.5));
        painter.end();
        ui->statusbar->showMessage("Das war leider nur Wasser.");
        playerBoard.get_Square_ptr(r,c)->set_hit();
    }
    ui->playerTable->setItem(r,c,new QTableWidgetItem(QIcon(QPixmap::fromImage(temp)),"",1000));
    game.change_activity_status();

}

void PlayWindow::setBomb(int r, int c)
{
    if(enemyBoard.get_Square_ptr((size_t)r,(size_t)c)->get_square_hit()){
        ui->statusbar->showMessage("Dieses Feld wurde schon bombardiert.");
        return;
    }
    if(game.getEnemyState()){
        ui->statusbar->showMessage("Der andere Spieler ist am Zug.");
        return;
    }
    int size = ui->enemyTable->iconSize().height();
    QImage temp("images/sea.png");
    if(enemyBoard.get_Square_ptr((size_t)r,(size_t)c)->get_square_set()){
        pen.setColor(red);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2-0.5)),((size/2-0.5)));
        painter.end();
        ui->statusbar->showMessage("Yeaaaayyy das war der Gegner.");
        enemyBoard.get_Square_ptr(r,c)->set_hit();
    }
    else{
        pen.setColor(black);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2)-0.5),((size/2)-0.5));
        painter.end();
        ui->statusbar->showMessage("Das war leider nur Wasser.");
        enemyBoard.get_Square_ptr(r,c)->set_hit();
    }
    ui->enemyTable->setItem(r,c,new QTableWidgetItem(QIcon(QPixmap::fromImage(temp)),"",1000));
    game.change_activity_status();
}

// Set the size, headernames of the rows and columns and fills the enemyTable with sea-Items
void PlayWindow::tableManagement()
{
    QTableWidget *table;
    for(int k=1;k<3;k++){
        if(k==1)
            table = ui->playerTable;
        else
            table = ui->enemyTable;

        qDebug("    tableManagement");
        table->setRowCount(width);
        table->setColumnCount(height);
        // set the headernames of the rows and columns
        QStringList hlist, vlist;
        vlist<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"
            <<"14"<<"15"<<"16"<<"17"<<"18"<<"19"<<"20";
        hlist<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"
            <<"O"<<"P"<<"Q"<<"R"<<"S"<<"T";
        table->setHorizontalHeaderLabels(hlist.mid(0,width));
        table->setVerticalHeaderLabels(vlist.mid(0,height));

        // manage the size of the squares of the table
        for(int i=0;i<height;i++)
            table->setColumnWidth(i,sqSize);
        for(int i=0;i<width;i++)
            table->setRowHeight(i,sqSize);

        // fills the fields of the table with squareg items
        QPixmap pixmap("images/sea.png");
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                if(k == 2){
                    if(enemyBoard.get_Square_ptr(i,j)->get_square_set()){
                        QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon("images/white.png"),"",1000);
                        table->setItem(i,j,tempItem);
                        table->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));
                    }
                    else{
                        QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon(pixmap),"",1000);
                        table->setItem(i,j,tempItem);
                        table->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));
                    }
                }
                else{
                    QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon(pixmap),"",1000);
                    table->setItem(i,j,tempItem);
                    table->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));
                }
            }
        }
        table->setDragDropMode(QAbstractItemView::DropOnly);
        table->setIconSize(QSize(sqSize+3,sqSize+3));
    }
}

void PlayWindow::setGameRef(Game &_game)
{
    qDebug("    getGameRef");
    game = _game;

    enemyBoard = game.getEnemyBoardRef();
    playerBoard = game.getBoardRef();
    ui->label->setText(QString::fromStdString(game.get_player_name()));
}

void PlayWindow::setTableRef(QTableWidget *table)
{

}
