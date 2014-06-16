#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>

namespace Ui {
class EndDialog;
}

class EndDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndDialog(bool win, QWidget *parent = 0);
    ~EndDialog();

private:
    Ui::EndDialog *ui;
};

#endif // ENDDIALOG_H
