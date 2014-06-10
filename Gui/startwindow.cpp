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
    qDebug("StartWindow beendet.");
}


void StartWindow::getName(QString n)
{
    name = n;
    setW->setWindowTitle("Ship Happens - " + name);
}

void StartWindow::openGame()
{
    ui->statusBar->showMessage("Wait for network stuff.");
    // call network functions to host a game
    setW->show();
    hide();
}

void StartWindow::joinGame()
{
    listW = new ListWindow(this);
    // call network functions to join a game
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
    playW = new PlayWindow(setW->getGameRef(), this);
    setW->close();
    playW->setTableRef(setW->getTableRef());
    //playW->setGameRef((setW->getGameRef()));
    playW->show();

}
