#include "dialog_login.h"
#include "ui_dialog_login.h"
#include "QString"
#include <QMessageBox>
#include "functions.h"

Dialog_login::Dialog_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_login)
{
    ui->setupUi(this);


    edit = new Editing;

    client_socket = new QTcpSocket(this);
    client_socket->connectToHost("10.0.2.15",33333);//loopback (интерфейс обратной связи)

    connect(client_socket,SIGNAL(connected()),SLOT(slot_on_connected()));
    connect(client_socket,SIGNAL(readyRead()),SLOT(slot_ready_read()));
}

Dialog_login::~Dialog_login()
{
    delete ui;
    client_socket->close();
}

/*
 * Функция авторизации: на вход подаются переменные типа QString log и pass,
 * а на выход - отправка сообщения (message_to_server) на сервер (через slot_send_to_server)
*/
void Dialog_login::authorize(QString log, QString pass)
{
    QString message_to_server;
    message_to_server = log+"&"+pass;
    slot_send_to_server(message_to_server);
}

//Функция отправки сообщения на сервер, добавляем "auth&", чтобы понимать что происходит на сервере
void Dialog_login::on_Ok_clicked()
{
    slot_send_to_server("auth&"+ui->lineEdit_Password->text() +"&"+ ui->lineEdit_Login->text());
}

//Функция подключения к серверу
void Dialog_login::slot_on_connected()
{
}

/*
 * функция чтения сообщения, полученного от сервера, если пришло сообщение: "authorization yes ", - то авторизация успешна,
 * а если: "authorization error ", - то нет, и следует повторить попытку
*/
void Dialog_login::slot_ready_read()
{
    QByteArray array;
    std::string message = "";
    QString log = ui->lineEdit_Login->text();
    QString pass = ui->lineEdit_Password->text();


    while(client_socket->bytesAvailable()>0)
    {
        array = client_socket->readAll();
        message += array.toStdString();
    }
    if(message=="authorization yes ")
    {
        this->close();
        edit->show();
    }
}
// функция отправки сообщения на сервер
void Dialog_login::slot_send_to_server(QString message)
{
    QByteArray array;
    array.append(message);
    client_socket->write(array);
}

//функция отключения приложения
void Dialog_login::slot_disconnected()
{
    client_socket->close();
}

// кнопка отмены, для перехода в главное меню
void Dialog_login::on_Cancel_clicked()
{
    this->close();
    emit ShowMW();
}

