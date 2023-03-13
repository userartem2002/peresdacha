#include "functions.h"
#include "database.h"

/* Функция проверки логина/пароля: на вход подаются переменные типа std::string log и pass, в которых
 * находятся данные, введенные пользователем,
если авторизация успешна, получаем сообщение: "authorization yes ", а если нет, то "authorization error " на выходе
*/
QString authorize(std::string log,std::string pass)
{
    QString  result;
    DataBase db;
    db.connectToDataBase();
    if (db.bdquery("select * from calls where number = '"+ QString::fromStdString(log) + "' AND code = '" + QString::fromStdString(pass) +"'") == "query done")
    {
        result = "authorization yes ";}
    else
        result = "authorization error ";

    return result;
}

QString bdquery(QString temp){
    QSqlQuery query;
    query.exec(temp);
    QString id, mile;
    QString array;
    while (query.next()) {
    id = query.value(0).toString();
    mile = query.value(1).toString();
    array.append(id);
    array.append("\t");
    array.append(mile);
    array.append("\t");
    array.append("\n");
    }
    return array;
}

QString bdquery2(QString temp){
    QSqlQuery query;
    query.exec(temp);
    QString id, departure, arrival, departure_time, flight_time;
    QString array2;
    while (query.next()) {
    id = query.value(0).toString();
    departure = query.value(1).toString();
    arrival = query.value(2).toString();
    departure_time = query.value(3).toString();
    flight_time = query.value(4).toString();
    array2.append(id);
    array2.append("\t");
    array2.append(departure);
    array2.append("\t");
    array2.append(arrival);
    array2.append("\t");
    array2.append(departure_time);
    array2.append("\t");
    array2.append(flight_time);
    array2.append("\n");
    }
    return array2;
}
