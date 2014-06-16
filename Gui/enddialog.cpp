#include "enddialog.h"
#include "ui_enddialog.h"

EndDialog::EndDialog(bool win, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndDialog)
{
    qDebug("        EndDialog");
    ui->setupUi(this);
    QGraphicsScene clown;
    if(win)
        clown.addPixmap(QPixmap("images/funny.png"));
    else
        clown.addPixmap(QPixmap("images/sad.png"));

    ui->graphicsView->setScene(&clown);
}

EndDialog::~EndDialog()
{
    qDebug("        ~EndDialog");
    delete ui;
}
