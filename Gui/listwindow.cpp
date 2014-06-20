#include "listwindow.h"
#include "ui_listwindow.h"

ListWindow::ListWindow(MySocket &s, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListWindow)
{
    ui->setupUi(this);
    socke = &s;
    setWindowTitle("Server wahl");
    setWindowIcon(QPixmap("images/ship.png"));

    connect(ui->StartButton, SIGNAL(clicked()), this, SLOT(startClicked()));
    connect(ui->CancleButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(setIP(QString)));
    connect(this, SIGNAL(connected()), parent, SLOT(listWindowClosed()));
}

ListWindow::~ListWindow()
{
    delete ui;
    qDebug("ListWindow beendet.");
}


void ListWindow::startClicked()
{
    ui->label_2->setText("Verbinden...");
    QString socketStr = socke->StartSocket(ip);
    if(socketStr == "true"){
        qDebug("Wieso springst du immer in diese Schleife?");
        emit connected();
    }
    else
        ui->label_2->setText(socketStr);
}

void ListWindow::setIP(QString i)
{
    ip = i;
}

