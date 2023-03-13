#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H

#include <QDialog>
#include "editing.h"
#include <QTcpSocket>

namespace Ui {
class Dialog_login;
}

class Dialog_login : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_login(QWidget *parent = nullptr);
    ~Dialog_login();

private:
    Ui::Dialog_login *ui;
    Editing *edit;
    QTcpSocket *client_socket;

signals:
    void ShowMW();//функция для возврата на окно MW

private slots:
    void on_Ok_clicked();//кнопка ок для проверки пары логин/пароль и перехода в режим редактирования
    void on_Cancel_clicked();// кнопка отмены, для перехода в главное меню
    void authorize(QString log, QString pass);// функция авторизации

private slots:
    void slot_on_connected();//функция подключения
    void slot_ready_read();// функция чтения сообщения, полученного от сервера
    void slot_send_to_server(QString message);// функция отправки сообщения на сервер
    void slot_disconnected();//функция отключения

};

#endif // DIALOG_LOGIN_H
