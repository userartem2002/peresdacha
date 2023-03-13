#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{
}

DataBase::~DataBase()
{
}

/* Функция для подключения к базе данных
 * */
/* Функция для открытия базы данных
 * */

bool DataBase::openDataBase()
{
    //closeDataBase();
    closeDataBase();
    //db = QSqlDatabase::addDatabase("QPSQL");
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



/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE_1 " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_NAME     " VARCHAR(255)    NOT NULL"
                            //TABLE_PHOTO      " BLOB            NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE_1;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}


/* Метод для вставки записи в базу данных
 * */
bool DataBase::insertIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */

    query.prepare("INSERT INTO " TABLE_1 " ( " TABLE_NAME ", "
                                             TABLE_DESCRIPRIOM ", "
                                             TABLE_EFFECTS " ) "
                  "VALUES (:name_photo, :descripriom, :effects)");
    query.bindValue(":name_photo",     data[0].toString());
    query.bindValue(":descripriom",     data[1].toString());
    query.bindValue(":effects",     data[2].toString());

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE_1;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}


bool DataBase::insertIntoTable(const QString &name_photo, const QString &descripriom, const QString &effects)
{
    QVariantList data;
    data.append(name_photo);
    //data.append(photo);
    data.append(descripriom);
    data.append(effects);

    if(insertIntoTable(data))
        return true;
    else
        return false;
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable2()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE_2 " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    PATIENT     " VARCHAR(255)    NOT NULL,"
                    DOCTOR     " VARCHAR(255)    NOT NULL,"
                    DATE     " VARCHAR(255)    NOT NULL,"
                    ADDRESS     " VARCHAR(255)    NOT NULL,"
                    SYMPTOMS     " VARCHAR(255)    NOT NULL,"
                    DIAGNOSYS     " VARCHAR(255)    NOT NULL,"
                    PRESCRIPTION     " VARCHAR(255)    NOT NULL,"
                    MEDECINE     " VARCHAR(255)    NOT NULL"
                " )"
            )){
qDebug() << "DataBase: error of create " << TABLE_2;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}


bool DataBase::insertIntoTable2(const QVariantList &data2)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */

    query.prepare("INSERT INTO " TABLE_2 " ( " PATIENT ", "
                                             DOCTOR ", "
                                             DATE ", "
                                             ADDRESS ", "
                                             SYMPTOMS ", "
                                             DIAGNOSYS ", "
                                             PRESCRIPTION ", "
                                             MEDECINE " ) "
                  "VALUES (:patient_name, :doctor_name, :date, :address, :symptoms, :diagnosis, :prescription, :medecine_id)");
    query.bindValue(":patient_name",     data2[0].toString());
    query.bindValue(":doctor_name",          data2[1].toString());
    query.bindValue(":date",     data2[2].toString());
    query.bindValue(":address",     data2[3].toString());
    query.bindValue(":symptoms",     data2[4].toString());
    query.bindValue(":diagnosis",          data2[5].toString());
    query.bindValue(":prescription",     data2[6].toString());
    query.bindValue(":medecine_id",     data2[7].toString());

    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE_2;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}


bool DataBase::insertIntoTable2(const QString &patient_name, const QString &doctor_name, const QString &date, const QString &address, const QString &symptoms, const QString &diagnosis, const QString &prescription, const QString &medecine_id)
{
    QVariantList data2;
    data2.append(patient_name);
    data2.append(doctor_name);
    data2.append(date);
    data2.append(address);
    data2.append(symptoms);
    data2.append(diagnosis);
    data2.append(prescription);
    data2.append(medecine_id);

    if(insertIntoTable2(data2))
        return true;
    else
        return false;
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

/*Функция запроса в БД*/
QString DataBase::bdquery2(QString temp){

    QSqlQuery query;
    query.exec(temp);
    while (query.next()) {
    QString name = query.value(0).toString();
    qDebug() << name;
    }

    //model->select();
}
