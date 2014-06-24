#include "Gui/startwindow.h"
#include "ui_startwindow.h"


/**
 * @brief StartWindow::StartWindow
 * @param parent
 * Constructor of the StartWindow-class
 * connects the signals of the Buttons and the LineEdit
 */
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

/**
 * @brief StartWindow::~StartWindow
 * Deconstructor
 */
StartWindow::~StartWindow()
{
    delete setW;
    delete playW;
    delete ui;
    qDebug("~StartWindow");
}

// Saves the name from the QLabel
/**
 * @brief StartWindow::getName
 * @param n
 * saves the name if the user entered it in the lineEdit
 */
void StartWindow::getName(QString n)
{
    name = n;
}

// Starts the server and opens the SetWindow
/**
 * @brief StartWindow::openGame
 * slot connected to the StartGame-Button
 * show the SetWindow and hides the StartWindow
 */
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
/**
 * @brief StartWindow::joinGame
 * slot connected to the join-Button
 * creats and shows a ListWindow and hide the StartWindow
 */
void StartWindow::joinGame()
{
    numb += 1;
    listW = new ListWindow(socket,this);
    host = false;
    listW->show();
    hide();
}

// Starts the SetWindow after the client connected to the server
/**
 * @brief StartWindow::listWindowClosed
 * slot connected to the Verbinden-Button in the ListWindow
 * close and delete the ListWindow
 * shows the SetWindow
 */
void StartWindow::listWindowClosed()
{
    listW->close();
    delete listW;
    setW->setWindowTitle("Ship Happens");
    setW->setHost(false);
    setW->show();
}

// Close the SetWindow and starts the PlayWindow
/**
 * @brief StartWindow::startGame
 * slot connected to the Start-Button in the SetWindow of the Host
 * close the SetWindow
 * creat and show the PlayWindow
 */
void StartWindow::startGame()
{
    //setW->getGameRef().player_print_boards();
    playW = new PlayWindow(host, setW->getGameRef(), this);
    setW->close();
    playW->show();

}

// Close the PlayWindow and start a new instance of SetWindow
/**
 * @brief StartWindow::revenge
 * slot connected to the quitSignal of the revenge() slot in PlayWindow
 * close the PlayWindow
 * delete the PlayWindow and the SetWindow
 * creat and show a new SetWindow
 */
void StartWindow::revenge()
{
    if(1){  //Abfrage ob beide Spieler revange wollen
        playW->close();
        delete playW;
        delete setW;
        setW = new SetWindow(this);
        setW->show();
    }
}

