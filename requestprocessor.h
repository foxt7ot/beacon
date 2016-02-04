#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H
#include <QTcpSocket>
#include <QObject>
#include <QThread>
#include <QString>
#include <QTextCodec>
#include <QStringList>
#include <QMap>

#include "globalresources.h"
class RequestProcessor : public QThread
{
    Q_OBJECT
public:
    explicit RequestProcessor(qintptr ptr,QObject *parent = 0);
    void run();
//    QString parseRequest(QString);
//    QString checkRequestType();
private :
    qintptr ptr;   //depends on system what type of value does the qintptr store
    //if the system is 32 bit qintptr is typedef for qint32 and if the system with
    //64-bit pointers qintptr is typedef for qint64
    quint16 portNumber;
    QTcpSocket *socket;
    QMap<QString, QString> map;
signals:
    void error(QTcpSocket::SocketError socketerror);
    void echo(QString);
public slots:
    void readyRead();
    void disconnected();
    
};

#endif // REQUESTPROCESSOR_H
