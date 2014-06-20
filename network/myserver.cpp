#include "myserver.h"

MyServer::MyServer(QObject *parent) :
    QObject(parent)
{

    server = new QTcpServer(this);

    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));


}

void MyServer::newConnection(){

    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(1000);

    socket->close();
}

void MyServer::startServer()
{
    if (!server->listen(QHostAddress::Any,1234)){

        //qDebug() << "Server could not start!";
    }
    else{

        //qDebug() << "Server started";
    }
}
