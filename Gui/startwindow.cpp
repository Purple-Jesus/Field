#include "Gui/startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    qDebug("StartWindow");
    setW = new SetWindow(this);
    ui->startGameButton->setAutoDefault(true);
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(getName(QString)));
    connect(ui->startGameButton, SIGNAL(clicked()), this, SLOT(openGame()));
    connect(ui->joinGameButton, SIGNAL(clicked()), this, SLOT(joinGame()));
}

StartWindow::~StartWindow()
{
    delete setW;
    delete playW;
    delete ui;
    qDebug("~StartWindow");
}


void StartWindow::getName(QString n)
{
    name = n;
    setW->setWindowTitle("Ship Happens");
}

void StartWindow::openGame()
{
    ui->statusBar->showMessage("Wait for network stuff.");
    server.startServer();
    host = true;
    setW->show();
    hide();
}

void StartWindow::joinGame()
{
    listW = new ListWindow(socket,this);
    // call network functions to join a game
    host = false;
    listW->show();
    hide();
}

void StartWindow::listWindowClosed()
{
    listW->close();
    delete listW;
    setW->show();
}

void StartWindow::startGame()
{
    setW->getGameRef().player_print_boards();
    playW = new PlayWindow(setW->getGameRef(), this);
    connect(this, SIGNAL(setStartActivity(bool)), playW, SLOT(getStartActivity(bool)));
    setW->close();
    //playW->setGameRef((setW->getGameRef()));
    emit setStartActivity(host);
    playW->show();

}

void StartWindow::revenge()
{
    playW->close();
    delete playW;
    show();
}


