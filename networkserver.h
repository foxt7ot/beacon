#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H
#include <QTcpServer>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include "requestprocessor.h"


class NetworkServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit NetworkServer(QObject *parent = 0);
    bool startServer();
protected:
    void incomingConnection(qintptr ptr);
signals:
    void echo(QString);
    
public slots:
    void receiveUpdate(QString);
    void onError(QTcpSocket::SocketError socketerror);
    
};

#endif // NETWORKSERVER_H
