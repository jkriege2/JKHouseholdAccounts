/**
 * Project: JKHouseholdAccounts (https://github.com/jkriege2/JKHouseholdAccounts)
 * Copyright (c) 2018, Jan Krieger <jan@jkrieger.de>
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef JKHADATABASETOOLS_H
#define JKHADATABASETOOLS_H

#include <QtSql>
#include <QObject>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QStringList>
#include <memory>
#include "jkhacategoriestreemodel.h"

enum class JKHABudgetType {
    Monthly=0,
    Yearly=1
};

QString JKHABudgetType2String(JKHABudgetType type);
QString JKHABudgetType2LocalString(JKHABudgetType type);

class JKHADatabase: public QObject {
    Q_OBJECT
public:
    JKHADatabase(QObject* parent);
    virtual ~JKHADatabase();
    /** \brief populates an item view for the overview table with the required models and delegates */
    void assignOverviewTable(QAbstractItemView* view);
    /** \brief populates an item view for the categories table with the required models and delegates */
    void assignCategoriesTable(QAbstractItemView* view);
    /** \brief populates an item view for the payers table with the required models and delegates */
    void assignPayersTable(QAbstractItemView* view);
    /** \brief populates an item view for the payees table with the required models and delegates */
    void assignPayeesTable(QAbstractItemView* view);

    /** \brief create a new database, stored in the file \a filename */
    void createNew(const QString& filename);
    /** \brief add a new expense to the opened database */
    void addExpense(const QDate& date, const QString& payee, const QString &payer, double amount, const QString &category, const QString& description, bool autorefresh=false);


    /** \brief returns a property from the SETTINGS-table in the current database */
    QVariant getDBProperty(const QString& property, const QVariant& defaultVal=QVariant()) const;
    /** \brief returns a property from the SETTINGS-table in the current database */
    int getDBPropertyInt(const QString& property, int defaultVal) const;
    /** \brief returns a property from the SETTINGS-table in the current database */
    bool getDBPropertyBool(const QString& property, bool defaultVal) const;
    /** \brief returns a property from the SETTINGS-table in the current database */
    double getDBPropertyDouble(const QString& property, double defaultVal) const;
    /** \brief returns a property from the SETTINGS-table in the current database */
    QString getDBPropertyString(const QString& property, const QString& defaultVal) const;
    /** \brief stores a property from the SETTINGS-table in the current database */
    void setDBProperty(const QString& property, double value);
    /** \brief stores a property in the SETTINGS-table in the current database */
    void setDBProperty(const QString& property, bool value);
    /** \brief stores a property in the SETTINGS-table in the current database */
    void setDBProperty(const QString& property, int value);
    /** \brief stores a property in the SETTINGS-table in the current database */
    void setDBProperty(const QString& property, const QString& value);
    /** \brief stores a property in the SETTINGS-table in the current database */
    void setDBProperty(const QString& property, const char* value);
    /** \brief read the current currency from the SETTINGS-table in the current database */
    QString getCurrency() const;


    /** \brief returns all super-categories */
    QStringList getSuperCategories() const;
    /** \brief returns the sub-categories for a given super-category \a superCat from the current database */
    QStringList getSubCategories(const QString& superCat, QList<int> *ids=nullptr) const;
    /** \brief returns the sub-category IDs for a given super-category \a superCat from the current database */
    QList<int> getSubCategoryIDs(const QString& superCat) const;
    /** \brief returns the categories list from the current database */
    QStringList getCategories() const;
    /** \brief ensures existence of a category to the categories list from the current database */
    int ensureCategory(const QString& name);
    /** \brief checks whether a category exists in the categories list from the current database */
    bool hasCategory(const QString& name, int *id=nullptr) const;
    /** \brief removes the category with the given ID */
    void removeCategory(int id);
    /** \brief returns a tree model of all catgories */
    JKHACategoriesTreeModel *getCategoriesTreeModel();
    /** \brief split a full category into super category and category name */
    QPair<QString, QString> splitFullCategory(const QString& cat) const;
    /** \brief returns the id of the given Category */
    int getCategoryID(const QString& cat) const;
    /** \brief returns the full name of the given Category */
    QString getCategoryFullName(int cat) const;

    /** \brief returns the payers list from the current database */
    QStringList getPayers() const;
    /** \brief ensures existence of a payer to the categories list from the current database */
    int ensurePayer(const QString& name);
    /** \brief checks whether a payer exists in the payers list from the current database */
    bool hasPayer(const QString& name, int* id=nullptr) const;

    /** \brief returns the payees list from the current database */
    QStringList getPayees() const;
    /** \brief ensures existence of a payee to the categories list from the current database */
    int ensurePayee(const QString& name);
    /** \brief checks whether a payee exists in the payees list from the current database */
    bool hasPayee(const QString& name, int* id=nullptr) const;



    /** \brief refresh the datamodels, i.e. rerun the query for the models */
    void refreshModels();
protected:
    /** \brief stores a property */
    void setDBProperty(const QString& property, const QVariant& value);

    void refreshCategoriesModel();
    void refreshExpensesModel();
    void refreshPayeeModel();
    void refreshPayerModel();
    void refreshBudgetsModel();
    void refreshRecurringExpensesModel();
    void refreshValueablesModel();

    static void debugLogQueryResult(QSqlQuery& q, const QString &name);

    QSqlRelationalTableModel *getOverviewModel();
    QSqlTableModel *getCategoriesModel();


    std::unique_ptr<QSqlRelationalTableModel>  m_overviewModel;
    std::unique_ptr<QSqlTableModel> m_categoriesModel;
    std::unique_ptr<QSqlRelationalTableModel> m_payeeModel;
    std::unique_ptr<QSqlTableModel> m_payerModel;
    std::unique_ptr<QSqlTableModel> m_budgetsModel;
    std::unique_ptr<QSqlRelationalTableModel> m_recurringExpensesModel;
    std::unique_ptr<QSqlRelationalTableModel> m_valueablesModel;
    std::unique_ptr<JKHACategoriesTreeModel> m_categoriesTreeModel;

    QSqlDatabase m_db;
    QSqlQuery m_query;
    void createModels();
};


#endif // JKHADATABASETOOLS_H
