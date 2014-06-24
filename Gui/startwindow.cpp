#include "Gui/startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    qDebug("StartWindow");
    setW = new SetWindow(this);
    numb = 0;

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

// Saves the name from the QLabel
void StartWindow::getName(QString n)
{
    name = n;
}

// Starts the server and opens the SetWindow
void StartWindow::openGame()
{
    numb += 1;
    ui->statusBar->showMessage("Wait for network stuff.");
    host = true;
    if(numb == 1)
        server.startServer();
    setW->setWindowTitle("Ship Happens");
    setW->setHost(true);
    setW->show();
    hide();
}

// Opens a window where you can enter the ip of the server and starts the client
void StartWindow::joinGame()
{
    numb += 1;
    listW = new ListWindow(socket,this);
    // call network functions to join a game
    host = false;
    listW->show();
    hide();
}

// Starts the SetWindow after the client connected to the server
void StartWindow::listWindowClosed()
{
    listW->close();
    delete listW;
    //delete setW;
    setW->setWindowTitle("Ship Happens");
    //setW->clearTable();
    setW->setHost(false);
    setW->show();
}

// Close the SetWindow and starts the PlayWindow
void StartWindow::startGame()
{
    setW->getGameRef().player_print_boards();
    playW = new PlayWindow(host, setW->getGameRef(), this);
    //connect(this, SIGNAL(setStartActivity(bool)), playW, SLOT(getStartActivity(bool)));
    setW->close();
    //playW->setGameRef((setW->getGameRef()));
    //emit setStartActivity(host);
    playW->show();

}

// Close the PlayWindow and start a new instance of SetWindow
void StartWindow::revenge()
{
    playW->close();
    delete playW;
    delete setW;
    setW = new SetWindow(this);
    setW->show();
}

