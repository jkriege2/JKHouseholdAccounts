#include "dlgaccountaddexpense.h"
#include "ui_dlgaccountaddexpense.h"


DlgAccountAddExpense::DlgAccountAddExpense(JKHADatabase* db, QWidget *parent) :
    QDialog(parent),
    m_db(db),
    ui(new Ui::DlgAccountAddExpense)
{
    ui->setupUi(this);
    ui->labCurrency->setText(m_db->getCurrency());
    ui->edtDate->setDate(QDate::currentDate());
    ui->cmbPayee->addItems(m_db->getPayees());
    ui->cmbPayer->addItems(m_db->getPayers());
    ui->cmbCategory->addItems(m_db->getCategories());
    ui->cmbPayee->setCurrentText("");
    ui->cmbCategory->setCurrentText("");
    connect(this, &QDialog::accepted, this, &DlgAccountAddExpense::addRecords);
}

DlgAccountAddExpense::~DlgAccountAddExpense()
{
    delete ui;
}

void DlgAccountAddExpense::addRecords()
{
    m_db->addExpense(ui->edtDate->date(),
                     ui->cmbPayee->currentText(),
                     ui->cmbPayer->currentText(),
                     ui->spinAmount->value(),
                     ui->cmbCategory->currentText(),
                     ui->edtDescription->text(), true);

}

void DlgAccountAddExpense::showMore(bool show)
{

}
