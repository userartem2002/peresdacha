#include "editing.h"
#include "ui_editing.h"
//#include "dialog_login.h"
#include <QBuffer>
#include <QScreen>
#include <QApplication>
#include <QFileDialog>
#include <QDialog>
#include <QSqlQueryModel>
#include <QImage>
#include <QPixmap>
#include <QColor>
#include <QMessageBox>


Editing::Editing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editing)
{
    ui->setupUi(this);

    client_socket = new QTcpSocket(this);
    client_socket->connectToHost("10.0.2.15",33333);//loopback (интерфейс обратной связи)

    connect(client_socket,SIGNAL(connected()),SLOT(slot_on_connected()));
    connect(client_socket,SIGNAL(readyRead()),SLOT(slot_ready_read()));
}

void Editing::slot_on_connected()
{

}
void Editing::exec(QString temp)
{
    QString message_to_server;
    message_to_server = temp;
    slot_send_to_server(message_to_server);
}

//Функция отправки сообщения на сервер, добавляем "auth&", чтобы понимать что происходит на сервере
void Editing::on_Send_exec_clicked()
{
    QString query = "SELECT mile from passenger";
    slot_send_to_server(query);
}


void Editing::slot_ready_read()
{
    QByteArray array;
    std::string message = "";



    while(client_socket->bytesAvailable()>0)
    {
        array = client_socket->readAll();
        message += array.toStdString();
    }
    ui->exec_from_server->setText(QString::fromStdString(message));

}
// функция отправки сообщения на сервер
void Editing::slot_send_to_server(QString message)
{
    QByteArray array;
    array.append(message);
    client_socket->write(array);
}

//функция отключения приложения
void Editing::slot_disconnected()
{
    client_socket->close();
}



Editing::~Editing()
{
    delete ui;
}
