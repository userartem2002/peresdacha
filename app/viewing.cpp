#include "viewing.h"
#include "ui_viewing.h"

Viewing::Viewing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Viewing)
{
    ui->setupUi(this);
    client_socket = new QTcpSocket(this);
    client_socket->connectToHost("10.0.2.15",33333);//loopback (интерфейс обратной связи)

    connect(client_socket,SIGNAL(connected()),SLOT(slot_on_connected()));
    connect(client_socket,SIGNAL(readyRead()),SLOT(slot_ready_read()));
}

void Viewing::slot_on_connected()
{

}
void Viewing::exec(QString temp)
{
    QString message_to_server;
    message_to_server = temp;
    slot_send_to_server(message_to_server);
}

//Функция отправки сообщения на сервер, добавляем "auth&", чтобы понимать что происходит на сервере
void Viewing::on_Send_exec_clicked()
{
    QString query = "select * from flight";
    slot_send_to_server(query);
}


void Viewing::slot_ready_read()
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
void Viewing::slot_send_to_server(QString message)
{
    QByteArray array;
    array.append(message);
    client_socket->write(array);
}

//функция отключения приложения
void Viewing::slot_disconnected()
{
    client_socket->close();
}

Viewing::~Viewing()
{
    delete ui;
}


void Viewing::on_back_clicked()
{
    this->close();
    emit ShowMW();
}

