#include "squareg.h"

SquareG::SquareG(int Size, QWidget *parent, Qt::WindowFlags f)
    :QLabel(parent,f), size(Size), set(FALSE), hit(FALSE), disabled(FALSE),
    sea(QImage("images/sea.png")),
    left(QImage("images/left.png")),
    right(QImage("images/right.png")),
    hmiddle(QImage("images/hmiddle.png")),
    top(QImage("images/top.png")),
    bottom(QImage("images/bottom.png")),
    vmiddle(QImage("images/vmiddle.png")),
    black(QColor(0,0,0)), red(QColor(255,0,0))
{
    pen.setWidth(10);
    pen.setJoinStyle(Qt::RoundJoin);
    sea = sea.scaled(size,size);
    setPixmap(QPixmap::fromImage(sea));
}


SquareG::SquareG(Square &_sq, QWidget *parent, Qt::WindowFlags f)
{
    SquareG(40,parent,f);
    sq = &_sq;
}

void SquareG::setSet(char p, bool _own, QString dir)
{
    own = _own;
    set = TRUE;
    position = p;
    direction = dir;
    QImage temp = sea;
    if(own){
        if(dir == "v"){
            if(position == 'm')
                temp = vmiddle;
            else if (position =='r')
                temp = bottom;
            else
                temp = top;
        }
        else{
            if(position == 'm')
                temp = hmiddle;
            else if (position =='l')
                temp = right;
            else
                temp = left;
        }
}
temp = temp.scaled(size,size);
setPixmap(QPixmap::fromImage(temp));
}


void SquareG::setHit()
{
//	if(i!=id){
    hit = TRUE;
    QImage temp;
    if(set){
        if(own){
            if(direction == "v"){
                if(position == 'm')
                    temp = vmiddle;
                else if (position =='r')
                    temp = bottom;
                else
                    temp = top;
            }
            else{
                if(position == 'm')
                    temp = hmiddle;
                else if (position =='l')
                    temp = right;
                else
                    temp = left;
            }
        }
        pen.setColor(red);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2-0.5)),((size/2-0.5)));
        painter.end();
    }
    else{
        temp = sea;
        pen.setColor(black);
        painter.begin(&temp);
        painter.setPen(pen);
        painter.drawPoint(((size/2)-0.5),((size/2)-0.5));
        painter.end();
    }
    temp = temp.scaled(size,size);
    setPixmap(QPixmap::fromImage(temp));
//	}
}

