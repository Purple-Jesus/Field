#include "listwindow.h"
#include "ui_listwindow.h"

ListWindow::ListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListWindow)
{
    ui->setupUi(this);
    setWindowTitle("Server wahl");
    connect(ui->StartButton, SIGNAL(clicked()), parent, SLOT(windowClosed()));
    connect(ui->CancleButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(setIP(QString)));
    setWindowIcon(QPixmap("images/ship.png"));
}

ListWindow::~ListWindow()
{
    delete ui;
    qDebug("ListWindow beendet.");

}


void ListWindow::startClicked()
{
    close();
}

void ListWindow::setIP(QString i)
{
    ip = i;
}

