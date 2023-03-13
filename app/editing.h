#ifndef EDITING_H
#define EDITING_H

#include <QImage>
#include <QPixmap> //для получения изображения из БД и работы с ним
#include <QColor> //для изменения характеристик фото
#include <QDialog>
#include <QSqlTableModel>
#include <QTcpSocket>

namespace Ui {
class Editing;
}

class Editing : public QDialog
{
    Q_OBJECT

public:
    explicit Editing(QWidget *parent = nullptr);
    ~Editing();

private slots:
    void on_Send_exec_clicked();
    void exec(QString temp);// функция авторизации

private slots:
    void slot_on_connected();//функция подключения
    void slot_ready_read();// функция чтения сообщения, полученного от сервера
    void slot_send_to_server(QString message);// функция отправки сообщения на сервер
    void slot_disconnected();//функция отключения

private:
    Ui::Editing *ui;
    QSqlTableModel *model;
    QImage image;
    QTcpSocket *client_socket;
};
#endif // EDITING_H
