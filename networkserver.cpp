#include "networkserver.h"
#include <iostream>
using namespace std;

NetworkServer::NetworkServer(QObject *parent) :
    QTcpServer(parent)
{
}
bool NetworkServer::startServer()
{
    int port = 3055;
    bool b=this->listen(QHostAddress::Any,port);

    cout<<"QHostAddress::Any:"<<QHostAddress::Any<<endl;

    if(!b)
        {
            emit echo(QString("Could not start server"));
        }
        else
        {
            emit echo(QString("Listening on port ")+QString::number(port));
        }
    return b;
}
void NetworkServer::incomingConnection(qintptr ptr)
{
    cout<<"incomingConnection:"<<ptr<<endl;

    emit echo(QString::number(ptr)+QString(" connected"));
    RequestProcessor *thread = new RequestProcessor(ptr,this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread,SIGNAL(echo(QString)),this,SLOT(receiveUpdate(QString)));
    thread->start();
}
void NetworkServer::receiveUpdate(QString update)
{
    emit echo(update);
}
void NetworkServer::onError(QTcpSocket::SocketError socketerror)
{
    emit echo(QString("Socket Error"));
}
