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
    //ui->cmbCategory->setDatabase(m_db);
    ui->cmbPayee->setCurrentText("");
    ui->cmbCategory->setCurrentText("");
    ui->cmbDir->setCurrentIndex(0);
    connect(this, &QDialog::accepted, this, &DlgAccountAddExpense::addRecords);
}

DlgAccountAddExpense::~DlgAccountAddExpense()
{
    delete ui;
}

void DlgAccountAddExpense::addRecords()
{
    double sign=-1;
    if (ui->cmbDir->currentIndex()==1) sign=+1;

    m_db->addExpense(ui->edtDate->date(),
                     ui->cmbPayee->currentText(),
                     ui->cmbPayer->currentText(),
                     ui->spinAmount->value()*sign,
                     ui->cmbCategory->currentText(),
                     ui->edtDescription->text(), true);

}

void DlgAccountAddExpense::on_cmbDir_currentIndexChanged(int index)
{
    if (index==0) {
        ui->spinAmount->setStyleSheet("color: rgb(170, 0, 0);");
    } else {
        ui->spinAmount->setStyleSheet("color: rgb(0, 85, 0);");
    }
}


void DlgAccountAddExpense::showMore(bool show)
{

}
