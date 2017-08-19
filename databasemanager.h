#ifndef CDATABASEMANAGER_H
#define CDATABASEMANAGER_H

#include <QtSql>
#include <qstandarditemmodel.h>

class CDataBaseManager : public QObject
{
    Q_OBJECT

public:
    CDataBaseManager();
    ~CDataBaseManager();

    // изменить значение в ячейке (поиск по имени фильма)
    bool UpdateTableCell(const QVariant &tableName,const QVariant &key, const QVariant &colName, const QVariant &value);

    // прочитать все записи из бвзы данных
    void SelectAllRecords(const QString &_tableName,QStandardItemModel *_pModel);

    // прочитать записи с учетом фильтра
    void SelectFilterRecords(const QString &_tableName,QVariantList &filterList,QStandardItemModel *_pModel);

    // прочитать информацию из ячейки (поиск по имени фильма)
    void SelectTableCell(const QVariant &_tableName, const QVariant &colName, QVariantList &keyPair, QVariant &out);

    // добавить запись в базу данных
    bool InserIntoTable(QVariant &Name, QVariant &Director, QVariant Year,QVariant &Rating, QVariant &Info);

    // Открытие базы данных
    bool OpenDataBase(const QString &dbName);

    // Создание таблицы в базе данных
    bool CreateTable(const QString &tableName);

    // Закрытие базы данных
    void CloseDataBase();

private:

    QSqlDatabase m_SQdb;
};

#endif // CDATABASEMANAGER_H
