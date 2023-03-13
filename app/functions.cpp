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


    if (db.bdquery("select * from authoriz where login = '"+ QString::fromStdString(log) + "' AND password = '" + QString::fromStdString(pass) +"'") == "query done")
    {//db.closeDataBase();
        result = "authorization yes ";}
    else
        result = "authorization error ";
    //db.closeDataBase();
    return result;
}

QString bdquery2(QString temp){

    QSqlQuery query;
    query.exec(temp);
    QString id, name, effects, descr;
    QString array;
    while (query.next()) {
    id = query.value(0).toString();
    name = query.value(1).toString();
    effects = query.value(2).toString();
    descr = query.value(3).toString();
    array.append(id);
    array.append("\t");
    array.append(name);
    array.append("\t");
    array.append(effects);
    array.append("\t");
    array.append(descr);
    array.append("\n");
    }
    return array;

}
