#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QVariant>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define HOSTNAME "10.0.2.15"
#define DATABASE_NAME "maltsev_exam"
#define USER "postgres"
#define PASSWORD "12345678"


class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
    bool openDataBase();
//    bool restoreDataBase();
    void closeDataBase();
    QString bdquery(QString temp); //запрос В БД для сравнения логина и пароля
    QString bdquery2(QString temp);
    QSqlDatabase db;

};

#endif // DATABASE_H
