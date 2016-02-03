#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QStringList>
#include <QTcpSocket>
#include <QLabel>
#include "networkserver.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum serverModes{STOPPED,STARTED};
public slots:
    void echo(QString message);
    void startServer();
    void stopServer();
    void clientConnected();
private slots:
    void on_startServerButton_clicked();
private:
    Ui::MainWindow *ui;
    QIcon *startServerIcon;
    QIcon *stopServerIcon;
    serverModes serverStatus;
    NetworkServer *server;


};

#endif // MAINWINDOW_H
