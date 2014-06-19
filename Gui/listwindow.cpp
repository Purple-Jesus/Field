#include "listwindow.h"
#include "ui_listwindow.h"

ListWindow::ListWindow(MySocket &s, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListWindow)
{
    ui->setupUi(this);
    setWindowTitle("Server wahl");
    connect(ui->StartButton, SIGNAL(clicked()), this, SLOT(startClicked()));
    connect(ui->CancleButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(setIP(QString)));
    connect(this, SIGNAL(connected()), parent, SLOT(listWindowClosed()));
    setWindowIcon(QPixmap("images/ship.png"));
}

ListWindow::~ListWindow()
{
    delete ui;
    qDebug("ListWindow beendet.");
}


void ListWindow::startClicked()
{
    if(!socke->StartSocket(ip)){
        emit connected();
    }
    else
        ui->label_2->setText("Verbindungsaufbau fehlgeschlagen. Bitte erneut probieren!");
}

void ListWindow::setIP(QString i)
{
    ip = i;
}

