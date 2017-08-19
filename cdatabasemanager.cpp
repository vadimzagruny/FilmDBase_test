#include "cdatabasemanager.h"

CDataBaseManager::CDataBaseManager()
{

}

void CDataBaseManager::connectToDataBase()
{
    OpenDataBase();

    CreateTable();
}

 bool CDataBaseManager::OpenDataBase()
 {
     m_SQdb = QSqlDatabase::addDatabase("QSQLITE");
     m_SQdb.setDatabaseName("db_film.sqlite");

     if(!m_SQdb.open()){
        qDebug() << m_SQdb.lastError().text();
        qDebug() << "FAIL =( ";
        return false;
     }
     return true;
 }


bool CDataBaseManager::CreateTable()
{
    QSqlQuery query;

    QString str = "CREATE TABLE film_table ("
            "Name       VARCHAR(255),"
            "Director   VARCHAR(255),"
            "Year       integer,"
            "Janre      VARCHAR(255)"
            ");";

    bool isOK = query.exec(str);

    if(!isOK){
       qDebug() << "Table not created";
       qDebug() << query.lastError().text();
    }

    return isOK;
}

void CDataBaseManager::CloseDataBase()
{
    m_SQdb.close();
}

bool CDataBaseManager::InserIntoTable(const QString &Name, const QString &Director, const int Year,const QString &Janre)
{
     QSqlQuery query;

     query.prepare("INSERT INTO film_table (Name, Director, Year, Janre) "
                 "VALUES (:Name, :Director, :Year, :Janre)");

     query.bindValue(":Name",       Name);
     query.bindValue(":Director",   Director);
     query.bindValue(":Year",       Year);
     query.bindValue(":Janre",      Janre);

     bool isOK = query.exec();

     if(!isOK){
       qDebug() << " Data was not insert";
       qDebug() << query.lastError().text();
     }

     return isOK;
}

bool CDataBaseManager::RemoveRecord(const QString &Name)
{
    QSqlQuery query;

    query.prepare("DELETE FROM film_table WHERE Name = :Name");
    query.bindValue(":Name",Name);

    bool isOK = query.exec();

    if(!isOK){
      qDebug() << " Data was not delete";
      qDebug() << query.lastError().text();
    }
    return isOK;
}
