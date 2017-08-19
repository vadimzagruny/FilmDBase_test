#ifndef ADDTOTABLEDIALOG_H
#define ADDTOTABLEDIALOG_H

#include <QDialog>

namespace Ui {
class AddToTableDialog;
}

class AddToTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddToTableDialog(QWidget *parent = 0);
    ~AddToTableDialog();

    void GetData(QVariantList& varList);

private slots:
    void on_addButton_clicked();
    void on_canselButton_clicked();

    void on_nameLineEdit_textChanged(const QString &arg1);
    void on_directorLineEdit_textChanged(const QString &arg1);
    void on_yearLineEdit_textChanged(const QString &arg1);

private:

    bool isNemeFill;
    bool isDirectorFill;
    bool isYearFill;

    Ui::AddToTableDialog *ui;
};

#endif // ADDTOTABLEDIALOG_H
