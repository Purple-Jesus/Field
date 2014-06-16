#include "playwindow.h"
#include "ui_playwindow.h"

PlayWindow::PlayWindow(QTableWidget *table, Game _game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayWindow),
    game(_game),
    playerBoard(game.getBoardRef()),
    enemyBoard(game.getEnemyBoardRef()),
    black(QColor(0,0,0)), red(QColor(255,0,0))
{
    qDebug("    Playwindow");
    ui->setupUi(this);
    playerTmp = table;
    ui->centralwidget->setWindowTitle("Ship Happens - " + QString::fromStdString(game.get_player_name()));
    ui->label_2->setText("Gewaesser von " + QString::fromStdString(game.get_enemy_name()));
    width = 10;
    height = 10;
    sqSize = 45;
    pen.setWidth(10);
    pen.setJoinStyle(Qt::RoundJoin);
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
    if(game.getPlayerState()){
        ui->statusbar->showMessage("Der andere Spieler ist am Zug.",4000);
        return;
    }
    else
        ui->statusbar->showMessage("Du bist an der Reihe.");
    if(playerBoard.get_Square_ptr((size_t)c+1,(size_t)r+1)->get_square_hit()){
        ui->statusbar->showMessage("Dieses Feld wurde schon bombardiert.",4000);
        return;
    }

    int size = ui->enemyTable->iconSize().height();
    QImage temp("images/sea.png");
    if(playerBoard.get_Square_ptr((size_t)c+1,(size_t)r+1)->get_square_set()){
        pen.setColor(red);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2-0.5)),((size/2-0.5)));
        painter.end();
        ui->statusbar->showMessage("Yeaaaayyy das war ein gegnerisches Schiff.",5000);
    }
    else{
        pen.setColor(black);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2)-0.5),((size/2)-0.5));
        painter.end();
        ui->statusbar->showMessage("Das war leider nur Wasser.",5000);
    }
    ui->playerTable->setItem(r,c,new QTableWidgetItem(QIcon(QPixmap::fromImage(temp)),"",1000));
    playerBoard.get_Square_ptr((size_t)c+1,(size_t)r+1)->set_hit();
    if(game.change_activity_status()){
        qDebug("    KeinFenster?");
        end = new EndDialog(true,this);
    }

}

void PlayWindow::setBomb(int r, int c)
{
    if(game.getEnemyState()){
        ui->statusbar->showMessage("Der andere Spieler ist am Zug.",5000);
        return;
    }

    if(enemyBoard.get_Square_ptr((size_t)c+1,(size_t)r+1)->get_square_hit()){
        ui->statusbar->showMessage("Dieses Feld wurde schon bombardiert.",5000);
        return;
    }

    int size = ui->enemyTable->iconSize().height();
    QImage temp("images/sea.png");
    if(playerBoard.get_Square_ptr((size_t)(c+1),(size_t)(r+1))->get_square_set()){
        pen.setColor(red);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2-0.5)),((size/2-0.5)));
        painter.end();
        ui->statusbar->showMessage("Yeaaaayyy das war der Gegner.",5000);
        enemyBoard.get_Square_ptr((size_t)(c+1),(size_t)(r+1))->set_hit();
        if(game.change_activity_status()){
            end = new EndDialog(false,this);
        }
        game.change_activity_status();
    }
    else{
        pen.setColor(black);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2)-0.5),((size/2)-0.5));
        painter.end();
        ui->statusbar->showMessage("Das war leider nur Wasser.");
        enemyBoard.get_Square_ptr((size_t)(c+1),(size_t)(r+1))->set_hit();
        game.change_activity_status();

    }
    ui->enemyTable->setItem(r,c,new QTableWidgetItem(QIcon(QPixmap::fromImage(temp)),"",1000));
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
        QPixmap sea("images/sea.png");
        QPixmap top("images/top.png");
        QPixmap mid("images/middle.png");
        QPixmap bot("images/bottom.png");
        QPixmap left("images/left.png");
        QPixmap vmid("images/vmiddle.png");
        QPixmap right("images/right.png");
        for(size_t i=0;i<width;i++){
            for(size_t j=0;j<height;j++){
                if(k == 1){

                    if(playerBoard.get_Square_ptr(j+1, i+1)->get_square_set()){
                        QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon("images/white.png"),"",1000);
                        table->setItem(i,j,tempItem);
                        table->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));

                    }
                    else{
                        QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon(sea),"",1000);
                        table->setItem(i,j,tempItem);
                        table->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));
                    }
                    /* // Hier wird die info über die squares benötig ob anfang ende und ob horizontal oder vertikal
                       // Oder die anfangspunkte, richtungen, länge der einzelnen schiffe
                    QTableWidgetItem *item = new QTableWidgetItem(playerTmp->itemAt(i,j)->icon(),"",1000);
                    table->setItem(i,j,item);
                    */
                }
                else{
                    QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon(sea),"",1000);
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

    playerBoard = game.getBoardRef();
    ui->label->setText(QString::fromStdString(game.get_player_name()));
    ui->centralwidget->setWindowTitle("Ship Happens - " + QString::fromStdString(game.get_player_name()));
}


void PlayWindow::getStartActivity(bool host)
{
    qDebug("    getStartActivity");
    game.setStartActivity(host);
}
