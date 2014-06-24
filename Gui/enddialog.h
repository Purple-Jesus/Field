#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>


namespace Ui {
class EndDialog;
}

/**
 * @brief The EndDialog class
 * provides EndDialog window where the player is asked if he want to play a revenge or not
 */
class EndDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndDialog(std::string name, bool win, QWidget *parent = 0);
    ~EndDialog();

private:
    Ui::EndDialog *ui;
};

#endif // ENDDIALOG_H
