#ifndef SQUAREG_H
#define SQUAREG_H

#include <QLabel>
#include <QPainter>
#include "square.h"

class SquareG : public QLabel
{

    Q_OBJECT

 private:
    int size;					// Size of the square
    bool set;					// defines if this square is filled with a ship
    bool hit;					// defines if the ship is hit or not
    bool disabled;              // defines if the square is setable or not
    QString direction;			// defines if the ship is placed vertical(v) or horizontal(h)
    char position;				// defines if its the left(l), right(r) part of the ship or a middle(m) part
    QImage sea;					// Image to display water
    QImage left;				// Image to display the left part of a horizontal ship
    QImage right;				// Image to display the right part of a horizontal ship
    QImage hmiddle;				// Image to display a middle part of a horizontal ship
    QImage top;					// Image to display the top part of a vertical ship
    QImage bottom;				// Image to display the bottom part of a vertical ship
    QImage vmiddle;				// Image to display a middle part of a vertical ship
    QImage bone;                // Image to display the square i disabled
    QColor black,red;			// Colors for the "missle" black for hit water and red for hit ship
    QPen pen;					// A pen to draw where the shoot hit
    QPainter painter;			// QPainter is needed to paint a picture
    bool own;               	// True if the ship on the square is your property
    Square *sq;                 // Reference to a square of the gamelogic



 public:
    SquareG(int Size, QWidget *parent = 0, Qt::WindowFlags f = 0);
    SquareG(Square &, QWidget *parent = 0, Qt::WindowFlags f = 0);

    void setSet(char, bool, QString);
    bool getSet()const{return set;}
    void clearSet(){set = FALSE;}

    void setHit();
    bool getHit()const {return hit;}
    void clearHit() {hit = FALSE;}

    void setDisable();
    bool getDisable()const {return disabled;}
    void clearDisable() {disabled = FALSE;};

    char getSite()const{return position;}

};

#endif // SQUAREG_H
