#include "mysocket.h"
#include <QString>
#include <QTextStream>
#include <string>
#include <iostream>

MySocket::MySocket(QObject *parent) :
    QObject(parent)
{
}

QString MySocket::StartSocket(QString ip){

    socket = new QTcpSocket(this);
    QTextStream cin(stdin);

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    //qDebug() << "Bitte Ip eingeben: ";
    //cin >> ip;

    //qDebug() << "Connecting...";

    socket->connectToHost(ip,1234);

    if (!socket->waitForConnected(3000)){
        return socket->errorString();
    }
    return "true";
}


void MySocket::connected()
{
    QByteArray board;

    socket->write(board);
}


void MySocket::disconnected(){

    qDebug() << "Disconnected!";
}

void MySocket::readyRead(){

    qDebug() << "Reading...";
    qDebug() << socket->readAll();
}
