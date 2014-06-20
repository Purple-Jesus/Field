#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>

class MySocket : public QObject
{
    Q_OBJECT
public:
    explicit MySocket(QObject *parent = 0);
    QString StartSocket(QString);

public slots:

    void connected();
    void disconnected();
    void readyRead();

private:

    QTcpSocket *socket;

};

#endif // MYSOCKET_H
