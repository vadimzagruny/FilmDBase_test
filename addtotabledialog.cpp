#include "addtotabledialog.h"
#include "ui_addtotabledialog.h"

AddToTableDialog::AddToTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddToTableDialog)
{
    ui->setupUi(this);

    isNemeFill      = false;
    isDirectorFill  = false;
    isYearFill      = false;

    // разрешение ввода только 4 цыфр для поля год
    QRegExp rxYear("[0-9]\\d{0,3}");
    QValidator *pValidator = new QRegExpValidator(rxYear, this);
    ui->yearLineEdit->setValidator(pValidator);

    // разрешение ввода только 1 цыфры от (0 до 9) для поля рейтинг
    QRegExp rxRating("[0-9]\\d{0}");
    pValidator = new QRegExpValidator(rxRating, this);
    ui->ratingLineEdit->setValidator(pValidator);
}

AddToTableDialog::~AddToTableDialog()
{
    delete ui;
}

void AddToTableDialog::GetData(QVariantList& varList)
{
    if(isNemeFill&&isDirectorFill&&isYearFill){
        varList.append(ui->nameLineEdit->text());
        varList.append(ui->directorLineEdit->text());
        varList.append(ui->yearLineEdit->text());
        varList.append(ui->ratingLineEdit->text());
        varList.append(ui->InfoLineEdit->text());
    }
}

//slots

void AddToTableDialog::on_addButton_clicked()
{
    this->accept();
}

void AddToTableDialog::on_canselButton_clicked()
{
    isNemeFill = isDirectorFill = isYearFill = false;
    this->reject();
}

void AddToTableDialog::on_nameLineEdit_textChanged(const QString &str)
{
    isNemeFill = !str.isEmpty();

    (isNemeFill&&isDirectorFill&&isYearFill) ?
                ui->addButton->setDisabled(false):
                ui->addButton->setDisabled(true);
}

void AddToTableDialog::on_directorLineEdit_textChanged(const QString &str)
{
    isDirectorFill = !str.isEmpty();

    (isNemeFill&&isDirectorFill&&isYearFill) ?
                ui->addButton->setDisabled(false):
                ui->addButton->setDisabled(true);
}

void AddToTableDialog::on_yearLineEdit_textChanged(const QString &str)
{
    isYearFill = !str.isEmpty();

    (isNemeFill&&isDirectorFill&&isYearFill) ?
                ui->addButton->setDisabled(false):
                ui->addButton->setDisabled(true);
}
