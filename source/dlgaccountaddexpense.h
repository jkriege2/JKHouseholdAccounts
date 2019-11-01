#ifndef DLGACCOUNTADDEXPENSE_H
#define DLGACCOUNTADDEXPENSE_H

#include <QDialog>
#include "jkhadatabasetools.h"
#include <QCloseEvent>

namespace Ui {
    class DlgAccountAddExpense;
}

class DlgAccountAddExpense : public QDialog
{
        Q_OBJECT

    public:
        explicit DlgAccountAddExpense(JKHADatabase* db, QWidget *parent = nullptr);
        ~DlgAccountAddExpense();

    protected slots:
        void addRecords();
        void showMore(bool show);

        void on_cmbDir_currentIndexChanged(int index);
    private:
        JKHADatabase* m_db;
        Ui::DlgAccountAddExpense *ui;
};

#endif // DLGACCOUNTADDEXPENSE_H
