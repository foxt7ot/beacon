#include "requestprocessor.h"
#include <iostream>
using namespace std;

RequestProcessor::RequestProcessor(qintptr ptr, QObject *parent) :
    QThread(parent)
{
    this->ptr=ptr;
}
void RequestProcessor::run()
{
    emit echo(QString("Processor Thread started"));
    socket=new QTcpSocket();
    if(!socket->setSocketDescriptor(this->ptr))
        {
            emit error(socket->error());
            return;
        }
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    emit echo(QString("Client connected on local port ")+QString::number(socket->localPort()));

    portNumber=socket->localPort();
    exec();
}
void RequestProcessor::readyRead()
{
    QByteArray data = socket->readAll();
    QString request(data);
    QString response;
    cout<<"*******"+request.toStdString()<<endl;
// code to process request over here

    response = parseRequest(request);
//    cout<<"readyRead executed"<<endl;

    emit echo(QString("Received : ")+QString(request));
    socket->write(response.toStdString().c_str());
    socket->flush();
    emit echo(QString("Response sent : ")+response);
}
void RequestProcessor::disconnected()
{
    emit echo(QString::number(ptr)+QString(" Client disconnected "));
    socket->deleteLater();
    exit(0);
}

QString RequestProcessor::parseRequest(QString request){
    if(request.startsWith(GlobalResources::beginingWith)!=1){
        return "Invalid request";
    }else if(request.endsWith(GlobalResources::endingWith)!=1){
        return "Invalid request";
    }else if(request.contains(GlobalResources::ending)!=1){
        return "Invalid request";
    }
    int startChopLength, endChopLength;
    startChopLength = GlobalResources::beginingWith.length();
    endChopLength = GlobalResources::endingWith.length()+GlobalResources::ending.length()+1;
    request = request.mid(startChopLength,-1);
    request = request.left(request.length()-endChopLength);
    if(request.length()==0 || request.length()%2!=0){
        return "Invalid request";
    }
    QStringList stringList = request.split("^",QString::SkipEmptyParts);
    for(int i=0;i<stringList.size();i++){
        QString key, value;
        key = stringList.at(i);
        value = stringList.at(i+1);
        map.insert(key, value);
        i++;
    }
    QString paymentType = checkRequestType();
    return paymentType;
}

QString RequestProcessor::checkRequestType(){
    GlobalResources globalResources;
    QList<QString> keys=map.keys();
    if(map.contains(globalResources.saleKey)){
        QString paymentType = map.value(globalResources.saleKey);
        if(paymentType.compare(globalResources.saleCode)==0){
            //process sale request
            return "Sale Request";
        }else if(paymentType.compare(globalResources.returnCode)==0){
            //process return request
            return "Return Request";
        }
    }
    return "otherRequest";
}
