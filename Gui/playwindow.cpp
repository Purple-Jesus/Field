#include "playwindow.h"
#include "ui_playwindow.h"

PlayWindow::PlayWindow(bool h, Game _game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayWindow),
    game(_game),
    playerBoard(game.getBoardRef()),
    enemyBoard(game.getEnemyBoardRef()),
    black(QColor(0,0,0)), red(QColor(255,0,0)),
    host(h)
{
    qDebug("    Playwindow");
    ui->setupUi(this);
    //game.enemy_set_ship_test();
    //playerTmp = table;
    game.getEnemyBoardRef() = game.getBoardRef();
    ui->centralwidget->setWindowTitle("Ship Happens - " + QString::fromStdString(game.get_player_name()));
    ui->label_2->setText("Gewaesser von " + QString::fromStdString(game.get_enemy_name()));
    width = 10;
    height = 10;
    sqSize = 45;
    pen.setWidth(10);
    pen.setJoinStyle(Qt::RoundJoin);
    tableManagement();
    setWindowTitle("Ship Happens");

    connect(ui->enemyTable, SIGNAL(cellClicked(int,int)), this, SLOT(setBomb(int,int)));
    connect(ui->playerTable, SIGNAL(cellClicked(int,int)), this, SLOT(getBombed(int,int)));
    connect(this, SIGNAL(quitSignal()), parent, SLOT(revenge()));
}

PlayWindow::~PlayWindow()
{
    delete ui;
}

void PlayWindow::revenge()
{
    endD->close();
    this->close();
    emit quitSignal();
}

void PlayWindow::setBomb(int r, int c)
{
    if(game.getPlayerState()){
        ui->statusbar->showMessage("Der andere Spieler ist am Zug.",4000);
        return;
    }

    if(enemyBoard.get_Square_ptr((size_t)c+1,(size_t)r+1)->get_square_hit()){
        ui->statusbar->showMessage("Dieses Feld wurde schon bombardiert.",4000);
        return;
    }

    int size = ui->enemyTable->iconSize().height();
    QImage temp = QImage("images/white");
    if(enemyBoard.get_Square_ptr((size_t)(c+1),(size_t)(r+1))->get_square_set()){
        pen.setColor(Qt::black);
        painter.begin(&temp);
        painter.setPen(pen);
        for(int i=0;i<temp.height();i++)
            for(int j=0;j<temp.width();j++){
                painter.drawPoint(i,j);
            }
        painter.end();
        pen.setColor(red);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2-0.5)),((size/2-0.5)));
        painter.end();
        ui->statusbar->showMessage("Yeaaaayyy das war der Gegner.",4000);
        //enemyBoard.get_Square_ptr((size_t)(c+1),(size_t)(r+1))->set_hit();
        game.bomb_square((size_t)(c+1),(size_t)(r+1));
        if(game.change_activity_status()){
            endD = new EndDialog(game.get_player_name(),true,this);
            endD->show();
        }
        game.change_activity_status();
        //game.getPlayer().print_field();
        //game.getPlayer().print_ships();
    }
    else{
        pen.setColor(Qt::blue);
        painter.begin(&temp);
        painter.setPen(pen);
        for(int i=0;i<temp.height();i++)
            for(int j=0;j<temp.width();j++){
                painter.drawPoint(i,j);
            }
        painter.end();
        pen.setColor(black);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2)-0.5),((size/2)-0.5));
        painter.end();
        ui->statusbar->showMessage("Das war leider nur Wasser.",4000);
        enemyBoard.get_Square_ptr((size_t)(c+1),(size_t)(r+1))->set_hit();
        game.change_activity_status();

    }
    temp.scaledToHeight(5);
    temp.scaledToWidth(5);
    //ui->enemyTable->setItem(r,c,new QTableWidgetItem(QIcon(QPixmap::fromImage(temp)),"",1000));
    ui->enemyTable->item(r,c)->setBackground(temp);
}


void PlayWindow::getBombed(int r, int c)
{
    if(game.getPlayerState()){
        ui->statusbar->showMessage("Der andere Spieler ist am Zug.",4000);
        return;
    }

    int size = ui->enemyTable->iconSize().height();
    QImage temp = QImage("images/sea.png");
    if(playerBoard.get_Square_ptr((size_t)(c+1),(size_t)(r+1))->get_square_set()){
        pen.setColor(Qt::black);
        painter.begin(&temp);
        painter.setPen(pen);
        for(int i=0;i<temp.height();i++)
            for(int j=0;j<temp.width();j++){
                painter.drawPoint(i,j);
            }
        painter.end();
        pen.setColor(red);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2-0.5)),((size/2-0.5)));
        painter.end();
        ui->statusbar->showMessage("Yeaaaayyy das war der Gegner.",4000);
        //enemyBoard.get_Square_ptr((size_t)(c+1),(size_t)(r+1))->set_hit();
        game.bomb_square((size_t)(c+1),(size_t)(r+1));
        if(game.change_activity_status()){
            endD = new EndDialog(game.get_player_name(),true,this);
            endD->show();
        }
        game.change_activity_status();
        //game.getPlayer().print_field();
        //game.getPlayer().print_ships();
    }
    else{
        pen.setColor(Qt::blue);
        painter.begin(&temp);
        painter.setPen(pen);
        for(int i=0;i<temp.height();i++)
            for(int j=0;j<temp.width();j++){
                painter.drawPoint(i,j);
            }
        painter.end();
        pen.setColor(black);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2)-0.5),((size/2)-0.5));
        painter.end();
        ui->statusbar->showMessage("Das war leider nur Wasser.");
        playerBoard.get_Square_ptr((size_t)(c+1),(size_t)(r+1))->set_hit();
        game.change_activity_status();

    }
    ui->playerTable->item(r,c)->setBackground(QBrush(temp));
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
        for(size_t i=0;i<(size_t)width;i++){
            for(size_t j=0;j<(size_t)height;j++){
                if(k == 1){

                    if(playerBoard.get_Square_ptr(j+1, i+1)->get_square_set()){
                        //QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon("images/white.png"),"",1000);
                        QTableWidgetItem *tempItem = new QTableWidgetItem();
                        tempItem->setBackgroundColor(Qt::black);
                        table->setItem(i,j,tempItem);
                        table->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));

                    }
                    else{
                        //QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon(sea),"",1000);
                        QTableWidgetItem *tempItem = new QTableWidgetItem();
                        tempItem->setBackgroundColor(Qt::blue);
                        table->setItem(i,j,tempItem);
                        table->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));
                    }
                }
                else{
                    //QTableWidgetItem *tempItem = new QTableWidgetItem(QIcon(sea),"",1000);
                    QTableWidgetItem *tempItem = new QTableWidgetItem();
                    tempItem->setBackgroundColor(Qt::blue);
                    table->setItem(i,j,tempItem);
                    table->itemAt(i,j)->setSizeHint(QSize(sqSize,sqSize));
                }
            }
        }
        table->setDragDropMode(QAbstractItemView::DropOnly);
        table->setIconSize(QSize(sqSize+3,sqSize+3));
    }
}

/*
void PlayWindow::getStartActivity(bool host)
{
    qDebug("    getStartActivity");
    game.setStartActivity(host);
}
*/

void PlayWindow::quitGame()
{
    this->close();
}

/*
void PlayWindow::setGameRef(Game &_game)
{
    qDebug("    getGameRef");
    game = _game;

    playerBoard = game.getBoardRef();
    ui->label->setText(QString::fromStdString(game.get_player_name()));
    ui->centralwidget->setWindowTitle("Ship Happens - " + QString::fromStdString(game.get_player_name()));
}
*/

/*
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
    //playerBoard.get_Square_ptr((size_t)c+1,(size_t)r+1)->set_hit();
    if(playerBoard.get_Square_ptr((size_t)c+1,(size_t)r+1)->get_square_set()){
        playerBoard.get_Square_ptr((size_t)c+1,(size_t)r+1)->set_hit();
        pen.setColor(red);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2-0.5)),((size/2-0.5)));
        painter.end();
        ui->statusbar->showMessage("Yeaaaayyy das war ein gegnerisches Schiff.",5000);
        if(game.change_activity_status()){
            qDebug("    NoWindow?");
            end = new EndDialog(game.get_player_name(),false,this);
            end->show();
        }
        game.change_activity_status();
        qDebug("print_field");
        game.getPlayer().print_field();
        qDebug("pring_ships");
        game.getPlayer().print_ships();
    }
    else{
        pen.setColor(black);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2)-0.5),((size/2)-0.5));
        painter.end();
        ui->statusbar->showMessage("Das war leider nur Wasser.",5000);
        game.change_activity_status();
    }
    ui->playerTable->setItem(r,c,new QTableWidgetItem(QIcon(QPixmap::fromImage(temp)),"",1000));

}
*/
