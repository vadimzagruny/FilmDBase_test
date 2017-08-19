#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtotabledialog.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализациябазы данных
    m_pDBManager = new CDataBaseManager;

    m_pDBManager->OpenDataBase("db_film");
    m_pDBManager->CreateTable("film_table");

    // инициализация модели представления таблиц
    m_pModel = new QStandardItemModel;

    ui->tableView->setModel(m_pModel);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ClearTable();

    // заполняем таблицу
    m_pDBManager->SelectAllRecords("film_table",m_pModel);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    // подпись на события изменений данных в ячейках таблицы
    connect(ui->tableView->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this,SLOT(onDataChanged(QModelIndex,QModelIndex,QVector<int>)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pDBManager;
}

void MainWindow::ClearTable()
{
    //назначем заголовки столбцов
    QStringList horizHeader;
    horizHeader .append("Название");
    horizHeader .append("Режисcер");
    horizHeader .append("Год выпуска");
    horizHeader .append("Рейтинг");

    // очищаем таблицу
    m_pModel->clear();
    m_pModel->setHorizontalHeaderLabels(horizHeader);
}

bool MainWindow::ChackData(QVariantList &varList)
{
    QVariant nameToCheck     = varList[eName]; // Name
    QVariant directorToCheck = varList[eDirector]; // Director

    QVariant resData;
    QVariantList kayPair;
    kayPair.append(nameToCheck);
    kayPair.append("Name");



    // проверка наличия фильма с таким именем
   m_pDBManager->SelectTableCell("film_table","Name",kayPair,resData);

    if(nameToCheck == resData)
    {
        QMessageBox msgBox;

        msgBox.setWindowTitle("Error !");
        msgBox.setText("Фильм с таким названием уже есть в базе");
        msgBox.exec();
        return false;
    }

    kayPair[0] = directorToCheck;
    kayPair[1] = "Director";

    // проверка наличия фильма с таким режиссером
    m_pDBManager->SelectTableCell("film_table","Director",kayPair,resData);

    qDebug() << "resData = " << resData;
    if(directorToCheck != resData)
    {
        QMessageBox msgBox;

        msgBox.setWindowTitle("Warning !");
        msgBox.setText("Режиссер не найден в БД.");
        msgBox.setInformativeText("Добавить его и закончить добавление фильма?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Yes:
              // Yes was clicked
                return true;
          case QMessageBox::No:
             // No was clicked
              return false;
          default:
            return false;
        }
    }

    return true;
}

// slots

void MainWindow::on_addButton_pressed()
{
    // Диалог для записи нового фильма
    AddToTableDialog addDialog;
    addDialog.setModal(true);

    // проверка подтвержденияя записи
    if(!addDialog.exec())return;

    // получить информацию о фильме
    QVariantList varList;
    addDialog.GetData(varList);

    // проверка наличия фильма и режиссера
    if(!ChackData(varList))return;

    // добавить фильм в базу данных
    m_pDBManager->InserIntoTable(
            varList[eName],     //Name
            varList[eDirector], //Director
            varList[eYear],     //Year
            varList[eRating],   //Rating
            varList[eInfo]      //Info
           );

    // обновить таблицу интерфейса пользователя
    ClearTable();
    m_pDBManager->SelectAllRecords("film_table",m_pModel);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::on_infoButton_clicked()
{
    // определить в какой строке курсор
    int row = ui->tableView->currentIndex().row();

    // определить имя фильма
    QVariantList keyPair;
    keyPair.append( ui->tableView->model()->index(row,eName).data());
    keyPair.append("Name");

    QVariant InfoData;

    // прочитать описание фильма из ячейки в базе данных
    m_pDBManager->SelectTableCell("film_table","Info",keyPair,InfoData);

    // вывести информацию о фильме на экран
    QMessageBox msgBox;

    msgBox.setWindowTitle("Film Info");
    msgBox.setText(InfoData.toString());
    msgBox.exec();

}

void MainWindow::on_findButton_clicked()
{
    // прочитать список фильтров
    QVariantList varList;
    varList.append(ui->filmLineEdit->text());
    varList.append(ui->yearLineEdit->text());
    varList.append(ui->raitingLineEdit->text());

    // обновить таблицу интерфейса пользователя с учетом фильтров
    ClearTable();
    m_pDBManager->SelectFilterRecords("film_table",varList,m_pModel);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::on_resetButton_clicked()
{
    // сбросить фильтры и
    // обновить таблицу интерфейса пользователя
    ClearTable();
    m_pDBManager->SelectAllRecords("film_table",m_pModel);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight,QVector<int>)
{
    // перезапись в базу только рейтинга
    if (ui->tableView->currentIndex().column() == eRating){

        // вычисление имени фильма для изменения
        int rowIdx =  ui->tableView->currentIndex().row();
        QVariant filmName = ui->tableView->model()->index(rowIdx,eName).data();

        m_pDBManager->UpdateTableCell("film_table",filmName,"Rating",topLeft.data());
    }
}
