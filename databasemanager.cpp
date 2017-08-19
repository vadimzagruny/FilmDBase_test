#include "databasemanager.h"

CDataBaseManager::CDataBaseManager()
{

}
 CDataBaseManager::~CDataBaseManager()
 {
     CloseDataBase();
 }


 bool CDataBaseManager::OpenDataBase(const QString &dbName)
 {
     m_SQdb = QSqlDatabase::addDatabase("QSQLITE");
     m_SQdb.setDatabaseName(dbName + ".sqlite");

     if(!m_SQdb.open()){
        qDebug() << m_SQdb.lastError().text();
        qDebug() << "FAIL =( ";
        return false;
     }
     return true;
 }


bool CDataBaseManager::CreateTable(const QString &tableName)
{
    QSqlQuery query;

    if(query.exec("SHOW TABLES"))return true;
    //film_table
    QString str = "CREATE TABLE " + tableName +" ("
            "Name       TEXT PRIMARY KEY,"
            "Director   TEXT,"
            "Year       integer,"
            "Rating     intager,"
            "Info       TEXT"
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

bool CDataBaseManager::InserIntoTable(QVariant &Name, QVariant &Director, QVariant Year, QVariant &Rating,QVariant &Info)
{
     QSqlQuery query;

     query.prepare("INSERT INTO film_table (Name, Director, Year, Rating, Info) "
                 "VALUES (:Name, :Director, :Year, :Rating, :Info)");

     query.bindValue(":Name",       Name);
     query.bindValue(":Director",   Director);
     query.bindValue(":Year",       Year);
     query.bindValue(":Rating",     Rating);
     query.bindValue(":Info",       Info);

     bool isOK = query.exec();

     if(!isOK){
       qDebug() << " Data was not insert";
       qDebug() << query.lastError().text();
     }

     return isOK;
}


 bool CDataBaseManager::UpdateTableCell(const QVariant &tableName,const QVariant &key, const QVariant &colName, const QVariant &value)
{
    QSqlQuery query;

    query.prepare("UPDATE "             +
                  tableName.toString()  +
                  " SET "               +
                  colName.toString()    +
                  " = "                 +
                  value.toString()      +
                  " WHERE '"            +
                  key.toString()        +
                  "' = Name");

    bool isOK = query.exec();

    if(!isOK){
      qDebug() << " Data was not update";
      qDebug() << query.lastError().text();
    }
    return isOK;
}

 void CDataBaseManager::SelectTableCell(const QVariant &tableName, const QVariant &colName, QVariantList &keyPair, QVariant &out)
 {
    QSqlQuery query;
    QString sel_str("SELECT "           +
                    colName.toString()  +
                    " FROM "            +
                    tableName.toString()+
                    " WHERE '"          +
                    keyPair[0].toString()+
                    "' = "              +
                    keyPair[1].toString());

     qDebug() << sel_str;
    bool isOK = query.exec(sel_str);
    if(!isOK){
      qDebug() << " Data was not select";
      qDebug() << query.lastError().text();
      return;
    }

    out = " No Data Here  =( ";

    while (query.next()) {
        out = query.value(0);
        out= out;
    }
 }

void CDataBaseManager::SelectFilterRecords(const QString &_tableName,QVariantList &filterList,QStandardItemModel *_pModel)
{
    QSqlQuery query;
    QString sel_str("SELECT * FROM "         +
                    _tableName               +
                    " WHERE '"               +
                    filterList[0].toString() +
                    "' = Name OR '"          +
                    filterList[1].toString() +
                    "' = Year OR '"          +
                    filterList[2].toString() +
                    "' = Rating"
                    );

    if(!query.exec(sel_str)){
        qDebug() << " Data was not select";
        qDebug() << query.lastError().text();
        return;
    }

    int NameFieldNo     = query.record().indexOf("Name");
    int DirectorFieldNo = query.record().indexOf("Director");
    int YearFieldNo     = query.record().indexOf("Year");
    int RatingFieldNo   = query.record().indexOf("Rating");

    QStandardItem *pItem;

    int row = 0;
    while (query.next()) {
        QString Name        = query.value(NameFieldNo).toString();
        pItem = new QStandardItem(Name);
        pItem->setEditable(false);
        _pModel->setItem(row,0,pItem);
        QString Director    = query.value(DirectorFieldNo).toString();
        pItem = new QStandardItem(Director);
        pItem->setEditable(false);
        _pModel->setItem(row,1,pItem);
        QString Year        = query.value(YearFieldNo).toString();
        pItem = new QStandardItem(Year);
        pItem->setEditable(false);
        _pModel->setItem(row,2,pItem);
        QString Rating       = query.value(RatingFieldNo).toString();
        pItem = new QStandardItem(Rating);
        pItem->setEditable(true);
        _pModel->setItem(row,3,pItem);
        ++row;
    }
}

void CDataBaseManager::SelectAllRecords(const QString &_tableName,QStandardItemModel *_pModel)
{
    QSqlQuery query;
    QString sel_str("SELECT * FROM " + _tableName);

    if(!query.exec(sel_str)){
        qDebug() << " Data was not select";
        qDebug() << query.lastError().text();
        return;
    }

    int NameFieldNo     = query.record().indexOf("Name");
    int DirectorFieldNo = query.record().indexOf("Director");
    int YearFieldNo     = query.record().indexOf("Year");
    int RatingFieldNo   = query.record().indexOf("Rating");

    QStandardItem *pItem;

    int row = 0;
    while (query.next()) {
        QString Name        = query.value(NameFieldNo).toString();
        pItem = new QStandardItem(Name);
        pItem->setEditable(false);
        _pModel->setItem(row,0,pItem);
        QString Director    = query.value(DirectorFieldNo).toString();
        pItem = new QStandardItem(Director);
        pItem->setEditable(false);
        _pModel->setItem(row,1,pItem);
        QString Year        = query.value(YearFieldNo).toString();
        pItem = new QStandardItem(Year);
        pItem->setEditable(false);
        _pModel->setItem(row,2,pItem);
        QString Rating       = query.value(RatingFieldNo).toString();
        pItem = new QStandardItem(Rating);
        pItem->setEditable(true);
        _pModel->setItem(row,3,pItem);
        ++row;
    }
}
