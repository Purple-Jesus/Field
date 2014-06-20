#include "enddialog.h"
#include "ui_enddialog.h"

EndDialog::EndDialog(std::string name, bool win, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndDialog)
{
    qDebug("        EndDialog");
    ui->setupUi(this);
    if(win){
        ui->picture->setPixmap(QPixmap("images/funny.png"));
        ui->label->setText("Herzlichen Glueckwunsch " + QString::fromStdString(name) + ", du hast das Spiel Gewonnen");
    }
    else{
        ui->picture->setPixmap(QPixmap("images/sad.png"));
        ui->label->setText("Tut mir leid " + QString::fromStdString(name) + ", aber du hattest heute scheinbar kein Glueck");
    }
    connect(ui->pushButton, SIGNAL(clicked()), parent, SLOT(quitGame()));
    connect(ui->pushButton_2, SIGNAL(clicked()), parent, SLOT(revenge()));
}

EndDialog::~EndDialog()
{
    qDebug("        ~EndDialog");
    delete ui;
}
