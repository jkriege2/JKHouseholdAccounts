#include "dlgaccountaddexpense.h"
#include "ui_dlgaccountaddexpense.h"

DlgAccountAddExpense::DlgAccountAddExpense(const QString& currency, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAccountAddExpense)
{
    ui->setupUi(this);
    ui->labCurrency->setText(currency);
    ui->edtDate->setDate(QDate::currentDate());
}

DlgAccountAddExpense::~DlgAccountAddExpense()
{
    delete ui;
}

QDate DlgAccountAddExpense::getDate() const
{
    return ui->edtDate->date();
}

double DlgAccountAddExpense::getAmount() const
{
    return ui->spinAmount->value();
}

QString DlgAccountAddExpense::getPayee() const
{
    return ui->cmbPayee->currentText();
}

QString DlgAccountAddExpense::getDescription() const
{
    return ui->cmbDescription->currentText();
}
