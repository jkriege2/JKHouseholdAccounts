#ifndef DLGACCOUNTADDEXPENSE_H
#define DLGACCOUNTADDEXPENSE_H

#include <QDialog>

namespace Ui {
    class DlgAccountAddExpense;
}

class DlgAccountAddExpense : public QDialog
{
        Q_OBJECT

    public:
        explicit DlgAccountAddExpense(const QString &currency, QWidget *parent = nullptr);
        ~DlgAccountAddExpense();

        QDate getDate() const;
        double getAmount() const;
        QString getPayee() const;
        QString getDescription() const;


    private:
        Ui::DlgAccountAddExpense *ui;
};

#endif // DLGACCOUNTADDEXPENSE_H
