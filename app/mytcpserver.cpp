#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>
#include <QList>
#include "functions.h"
//#include "database.h"
MyTcpServer::~MyTcpServer()
{

    foreach(int i, SClients.keys())
    {
      QTextStream os (SClients[i]);
      SClients[i]->close();
      SClients.remove(i);
    }
    server_status=0;// присваиваем переменной  server_status значение 0
    mTcpServer->close();
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);
// Если сервер не открылся, выводим сообщение: "server is not started",
// а если открылся выводим сообщение "server is started"
// и присваиваем переменной  server_status значение 1
    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qWarning() << "server is not started";
    } else {
        server_status=1;
        qInfo() << "server is started";
    }
}

//функция подключения клиента
void MyTcpServer::slotNewConnection(){
    if(server_status==1){
        //Если переменная server_status имеет значение 1, что означает, что сервер запущен, выводим сообщение
        // "Hello, World!!! I am echo server!\r\n"
        QTcpSocket *clientSocket= mTcpServer->nextPendingConnection();
        int idusersocs=(int)clientSocket->socketDescriptor();
        SClients[idusersocs]=clientSocket;
        SClients[idusersocs]->write("");
        connect(SClients[idusersocs], &QTcpSocket::readyRead,this,&MyTcpServer::slotServerRead);
        connect(SClients[idusersocs],&QTcpSocket::disconnected,this,&MyTcpServer::slotClientDisconnected);
    }
}

// функция чтения сообщения, которое пришло от клиента
void MyTcpServer::slotServerRead(){
    QTcpSocket *clientSocket=(QTcpSocket*)sender();
    int id =(int)clientSocket->socketDescriptor();
    QByteArray array;
    std::string message= "";

    while(clientSocket->bytesAvailable()>0)
    {
        array =clientSocket->readAll();

    message += array.toStdString();
    }

        //qDebug()<< QString::fromStdString(message);


    std::string log = "";
    std::string pass = "";
    QString exec = "";
    qInfo()<<QString::fromStdString(message);
    int pos = message.find("&");
    message.erase(0,pos+1);

    //find login
    pos = message.find("&");
    log = message.substr(0,pos);
    //exec = message;
    message.erase(0,pos+1);

    // find password
    pos = message.find("&");
    pass = message.substr(0,pos);
    message.erase(0,pos+1);

    //Для работы с puTTy убираем лишние символы
    //pass.pop_back();
    //pass.pop_back();


    if (message.find("SELECT") == 0) {
        //qDebug()<< QString::fromStdString(message);

        array.clear();
        array.append(bdquery2(QString::fromStdString(message)));
    }
    else {
        qDebug()<<"login = " <<QString::fromStdString(log)
               <<"password = "<<QString::fromStdString(pass)
              <<"result = "<< authorize(log,pass);

        array.clear();
        array.append(authorize(log,pass));}

    clientSocket->write(array);
}

//функция отключения клиента, если клиент отключился, выводим сообщение: "Client is disconnected \n"
void MyTcpServer::slotClientDisconnected(){
    QTcpSocket *clientSocket = (QTcpSocket*) sender();
    int id =(int)clientSocket->socketDescriptor();
    clientSocket->close();
    SClients.remove(id);
    qWarning() <<QString::fromUtf8("Client is disconnected \n");
}
