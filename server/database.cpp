#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{
}

DataBase::~DataBase()
{
}


/* Функция для открытия базы данных
 * */

bool DataBase::openDataBase()
{
    closeDataBase();
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(HOSTNAME);
    db.setPort(5432);

    db.setDatabaseName(DATABASE_NAME);
    db.setUserName(USER);
    db.setPassword(PASSWORD);
    if (db.open())
    {
        qInfo()<<"db is open";
        return true;
    }
    else
    {
        qCritical()<<"db not open";
        return false;
    }
}

/* Функция для зыкрытия базы данных
 * */
void DataBase::closeDataBase()
{
    QSqlDatabase::removeDatabase(DATABASE_NAME);
    db.close();
    if (db.open())
    {
        qInfo()<<"db is open";

    }
    else
    {
        qCritical()<<"db not open";

    }
}
void DataBase::connectToDataBase()
{
    this->openDataBase();
}


/*Функция запроса в БД*/
QString DataBase::bdquery(QString temp){

    QSqlQuery query(db);
    query.exec(temp);
    query.next();
    if (query.value(0).toString().length() > 0)
    {
        return "query done";
    }
    else {
        return "query error";
    }
}

