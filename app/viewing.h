#ifndef VIEWING_H
#define VIEWING_H

#include <QDialog>
#include <QSqlTableModel>
#include <QTcpSocket>


namespace Ui {
class Viewing;
}

class Viewing : public QDialog
{
    Q_OBJECT

public:
    explicit Viewing(QWidget *parent = nullptr);
    ~Viewing();

private slots:
    void on_back_clicked();
    void on_Send_exec_clicked();
    void exec(QString temp);// функция авторизации
    void slot_on_connected();//функция подключения
    void slot_ready_read();// функция чтения сообщения, полученного от сервера
    void slot_send_to_server(QString message);// функция отправки сообщения на сервер
    void slot_disconnected();//функция отключения

signals:
    void ShowMW();//функция для возврата на окно MW

private:
    Ui::Viewing *ui;
    QSqlTableModel *model;
    QTcpSocket *client_socket;
};

#endif // VIEWING_H
