#ifndef CDATABASEMANAGER_H
#define CDATABASEMANAGER_H

#include <QtSql>


class CDataBaseManager : public QObject
{
    Q_OBJECT
public:
    CDataBaseManager();

    void connectToDataBase();

public slots:
    bool InserIntoTable(const QString &Name, const QString &Director, const int Year,const QString &Janre);
    bool RemoveRecord(const QString &Name);
private:

    bool OpenDataBase();        // Открытие базы данных
    bool CreateTable();         // Создание базы таблицы в базе данных
    void CloseDataBase();       // Закрытие базы данных

private:
    QSqlDatabase m_SQdb;
};

#endif // CDATABASEMANAGER_H
