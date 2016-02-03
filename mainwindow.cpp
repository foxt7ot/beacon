#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Simulator - Server");
    startServerIcon=new QIcon(QPixmap(":/Images/startIcon.png"));
    stopServerIcon=new QIcon(QPixmap(":/Images/stopIcon.png"));
    serverStatus= STOPPED;
    this->ui->startServerButton->setText("");
    this->ui->startServerButton->setIcon(*startServerIcon);
    this->ui->startServerButton->setIconSize(QSize(72,72));
    this->ui->startServerButton->setToolTip("Start Server");
    server=new NetworkServer(this);
    connect(server,SIGNAL(echo(QString)),this,SLOT(echo(QString)));
    this->ui->logTable->setColumnCount(1);
    this->ui->logTable->setColumnWidth(0,400);
    QStringList headers;
    headers<<"Log";
    this->ui->logTable->setHorizontalHeaderLabels(headers);
    this->ui->logTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->logTable->setSelectionMode(QAbstractItemView::SingleSelection);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startServer()
{
    if(server->startServer())
    {
        serverStatus=STARTED;
        this->ui->startServerButton->setText("");
        this->ui->startServerButton->setIcon(*stopServerIcon);
        this->ui->startServerButton->setToolTip("Stop Server");
        echo("Server started");
    } else
    {
        echo("Unable to start server : "+server->errorString());
    }
}
void MainWindow::stopServer()
{
    server->close();
    serverStatus=STOPPED;
    this->ui->startServerButton->setIcon(*startServerIcon);
    this->ui->startServerButton->setToolTip("Start Server");
    echo("Server stopped");
}
void MainWindow::clientConnected()
{
    cout<<"clientConnected executed"<<endl;
    echo("Client sent a request");
    QTcpSocket *socket=server->nextPendingConnection();
    RequestProcessor *requestProcessor;
    requestProcessor=new RequestProcessor(socket->socketDescriptor(),this);

    cout<<"socketDescriptor:"<<socket->socketDescriptor()<<endl;

    connect(requestProcessor,SIGNAL(finished()),requestProcessor,SLOT(deleteLater()));
    requestProcessor->start();
}
void MainWindow::echo(QString message)
{
     int rowIndex=this->ui->logTable->rowCount();

     cout<<"rowIndex:"<<rowIndex<<endl;

    this->ui->logTable->setRowCount(rowIndex+1);

    QLabel *label;
    label=new QLabel(this->ui->logTable);
    label->setText(message);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    this->ui->logTable->setCellWidget(rowIndex,0,label);

    cout<<"row  Index:"<<rowIndex<<endl;

    this->ui->logTable->selectRow(rowIndex);
}

void MainWindow::on_startServerButton_clicked()
{
    if(serverStatus==STOPPED)
    {
    this->startServer();
    }
    else
    {
    this->stopServer();
    }

}
