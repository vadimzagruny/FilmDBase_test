#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <qstandarditemmodel.h>
#include <QStandardItem>

#include "databasemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    // очистить таблицу
    void ClearTable();

    // проверить наличие фильмов с текущим именем и режиссером
    bool ChackData(QVariantList &varList);

private slots:

    void on_addButton_pressed();
    void on_infoButton_clicked();
    void on_findButton_clicked();
    void on_resetButton_clicked();
    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight,QVector<int>);

private:
    Ui::MainWindow *ui;

     CDataBaseManager   *m_pDBManager;
     QStandardItemModel *m_pModel;

     // индексы столбцов таблицы
     enum{
         eName = 0,
         eDirector,
         eYear,
         eRating,
         eInfo,
     };
};

#endif // MAINWINDOW_H
