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

#include "jkhadatabasetools.h"
#include <iomanip>
#include "jkcpptools.h"
#include "jkhamoneydelegate.h"
#include "jkhabudgettypedelegate.h"


JKHADatabase::JKHADatabase(QObject *parent):
    QObject(parent), m_overviewModel(nullptr), m_categoriesModel(nullptr)
{
}

JKHADatabase::~JKHADatabase()
{
    delete m_overviewModel;
    m_overviewModel=nullptr;
    delete m_categoriesModel;
    m_categoriesModel=nullptr;
    delete m_payeeModel;
    m_payeeModel=nullptr;
    delete m_payerModel;
    m_payerModel=nullptr;
    delete m_budgetsModel;
    m_budgetsModel=nullptr;
    delete m_recurringExpensesModel;
    m_recurringExpensesModel=nullptr;
    delete m_valueablesModel;
    m_valueablesModel=nullptr;
    m_db.commit();
    m_db.close();
}

void JKHADatabase::assignOverviewTable(QAbstractItemView *view)
{
    view->setModel(m_overviewModel);
    view->setItemDelegate(new QSqlRelationalDelegate(view));
    view->setItemDelegateForColumn(4, new JKHAMoneyDelegate(this, view, true));
}

QSqlRelationalTableModel *JKHADatabase::getOverviewModel()
{
    return m_overviewModel;
}

void JKHADatabase::assignCategoriesTable(QAbstractItemView *view)
{
    view->setModel(m_categoriesModel);
    //view->setItemDelegate(new QSqlRelationalDelegate(view));
    view->setItemDelegateForColumn(2, new JKHAMoneyDelegate(this, view, false));
    view->setItemDelegateForColumn(3, new JKHABudgetTypeDelegate(this, view));
}

void JKHADatabase::assignPayersTable(QAbstractItemView *view)
{
    view->setModel(m_payerModel);
}

void JKHADatabase::assignPayeesTable(QAbstractItemView *view)
{
    view->setModel(m_payeeModel);
}

QSqlTableModel *JKHADatabase::getCategoriesModel()
{
    return m_categoriesModel;
}

void JKHADatabase::createNew(const QString &filename)
{
    m_db.removeDatabase("QSQLITE");
    QFileInfo fn(filename);
    fn.makeAbsolute();
    QString absFN=fn.absoluteFilePath();
    bool dbexists=QFile::exists(absFN);
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug()<<absFN;
    qDebug()<<QDir::toNativeSeparators(absFN);
    m_db.setDatabaseName(QDir::toNativeSeparators(absFN));
    m_db.open();
    //m_db.open(user, pw);


    QSqlQuery query(m_db);
    if (!dbexists) {
        query.exec("CREATE TABLE settings ("
                     "  key VARCHAR(100) PRIMARY KEY NOT NULL"
                     ", value VARCHAR(200)"
                     ", type VARCHAR(200)"
                   ")");
        debugLogQueryResult(query, "createNew");
        query.exec("CREATE TABLE expenses ("
                       "  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT"
                       ", date DATE"
                       ", idPayee INT NOT NULL"
                       ", idPayer INT NOT NULL"
                       ", amount MONEY"
                       ", idCategory INT NOT NULL"
                       ", description VARCHAR(200)"
                   ")");
        debugLogQueryResult(query, "createNew");
        query.exec("CREATE TABLE recurringExpenses ("
                       "  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT"
                       ", dateStart DATE"
                       ", repeatMode INTEGER"
                       ", lastExecutedDate DATE"
                       ", idPayee INT NOT NULL"
                       ", idPayer INT NOT NULL"
                       ", amount MONEY"
                       ", idCategory INT NOT NULL"
                       ", description VARCHAR(200)"
                   ")");
        debugLogQueryResult(query, "createNew");
        query.exec("CREATE TABLE valueables ("
                       "  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT"
                       ", name VARCHAR(200)"
                       ", value MONEY"
                       ", category VARCHAR(200)"
                       ", idPayer INT NOT NULL"
                       ", description VARCHAR(200)"
                       ", dateAdded DATE"
                   ")");
        debugLogQueryResult(query, "createNew");
        query.exec("CREATE TABLE categories ("
                     "  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT"
                     ", name VARCHAR(200) NOT NULL"
                   ")");
        debugLogQueryResult(query, "createNew");
        query.exec("CREATE TABLE payers ("
                     "  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT"
                     ", name VARCHAR(200) NOT NULL"
                   ")");
        debugLogQueryResult(query, "createNew");
        query.exec("CREATE TABLE payees ("
                     "  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT"
                     ", name VARCHAR(200) NOT NULL"
                   ")");
        debugLogQueryResult(query, "createNew");
        query.exec("CREATE TABLE budgets ("
                     "  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT"
                     ", dateAdded DATE"
                     ", name VARCHAR(200)"
                     ", description VARCHAR(200)"
                   ")");
        debugLogQueryResult(query, "createNew");
        query.exec("CREATE TABLE budgetEntries ("
                     "  id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT"
                     ", idBudget INT NOT NULL"
                     ", idCategory INT NOT NULL"
                     ", budget MONEY"
                     ", budgetType INTEGER"
                   ")");
        debugLogQueryResult(query, "createNew");

        setDBProperty("CURRENCY", "EUR");
        addExpense(QDate(2018, 12, 23), "REWE", "JAN", 49.99, "Haushalt/Lebensmittel", "Weihnachtseinkauf");
        addExpense(QDate(2018, 12, 31), "REWE", "JAN", 17.85, "Haushalt/Lebensmittel", "Silvestereinkauf");
        addExpense(QDate(2018, 12, 31), "REWE", "Tabea", 23, "Haushalt/Lebensmittel", "Silvestereinkauf");
        addExpense(QDate(2018, 12, 31), "DM", "JAN",9.22, "Haushalt/Drogerie", "");
        addExpense(QDate(2018, 12, 12), "Photoladen", "JAN",539, "Hobby/Photographie", "Weihnachtsgeschenk");
    }

    createModels();
}

void JKHADatabase::addExpense(const QDate &date, const QString &payee, const QString &payer, double amount, const QString &category, const QString &description, bool autorefresh)
{
    int rcategory=ensureCategory(category);
    int rpayee=ensurePayee(payee);
    int rpayer=ensurePayer(payer);
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO expenses (id, date, amount, idPayee, idPayer, idCategory, description)"
                  " VALUES (null, :date, :amount, :payee, :payer, :category, :description)");
    query.bindValue(":date", date);
    query.bindValue(":amount", amount);
    query.bindValue(":payee", rpayee);
    query.bindValue(":payer", rpayer);
    query.bindValue(":category", rcategory);
    query.bindValue(":description", description);
    query.exec();
    debugLogQueryResult(query, "addExpense");
    if (autorefresh) refreshModels();
}

QString JKHADatabase::getCurrency() const
{
    return getDBPropertyString("CURRENCY", "EUR");
}

QStringList JKHADatabase::getCategories() const
{
    QStringList cats;
    QSqlQuery query(m_db);
    query.exec(QString("SELECT name FROM categories"));
    auto finalyact=jkfinally(std::bind(&debugLogQueryResult, query, "getCategories"));
    if (query.isActive() && query.next()) {
        bool ok=query.first();
        while (ok) {
            cats<<query.value(0).toString();
            ok=query.next();
        }
    }
    return cats;
}


int JKHADatabase::ensureCategory(const QString &name)
{
    int id=-1;
    if (hasCategory(name, &id)) return id;
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO categories (id, name) VALUES (null, :name)");
    query.bindValue(":name", name);
    query.exec();
    auto finalyact=jkfinally(std::bind(&debugLogQueryResult, query, "ensureCategory"));
    refreshCategoriesModel();
    if (hasCategory(name, &id)) return id;
    throw std::runtime_error("unable to add category");
}

bool JKHADatabase::hasCategory(const QString &name, int *id) const
{
    QSqlQuery query(m_db);
    query.exec(QString("SELECT id FROM categories WHERE name=='%1'").arg(name));
    auto finalyact=jkfinally(std::bind(&debugLogQueryResult, query, "hasCategory"));
    if (query.isActive() && query.next()) {
        bool ok=true;
        if (id) *id=query.value(0).toInt(&ok);
        if (id) qDebug()<<"*id="<<*id;
        qDebug()<<"value: "<< query.value(0);
        qDebug()<<"ok:    "<<ok;
        return ok;
    }
    return false;
}

void JKHADatabase::removeCategory(int id)
{
    QSqlQuery query(m_db);
    query.exec(QString("DELETE FROM categories WHERE id==%1").arg(id));
    debugLogQueryResult(query, "removeCategory");
    refreshCategoriesModel();
}



QStringList JKHADatabase::getPayees() const
{
    QStringList cats;
    QSqlQuery query(m_db);
    auto finalyact=jkfinally(std::bind(&debugLogQueryResult, query, "getPayees"));
    query.exec(QString("SELECT name FROM payees"));
    if (query.isActive() && query.next()) {
        bool ok=query.first();
        while (ok) {
            cats<<query.value(0).toString();
            ok=query.next();
        }
    }
    return cats;
}


int JKHADatabase::ensurePayee(const QString &name)
{
    int id=-1;
    if (hasPayee(name, &id)) return id;
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO payees (id, name) VALUES (null, :name)");
    query.bindValue(":name", name);
    query.exec();
    debugLogQueryResult(query, "ensurePayee");
    refreshPayeeModel();
    if (hasPayee(name, &id)) return id;
    throw std::runtime_error("unable to add payee");
}

bool JKHADatabase::hasPayee(const QString &name, int *id) const
{
    QSqlQuery query(m_db);
    query.exec(QString("SELECT id FROM payees WHERE name=='%1'").arg(name));
    auto finalyact=jkfinally(std::bind(&debugLogQueryResult, query, "hasPayee"));
    if (query.isActive() && query.next()) {
        bool ok=true;
        if (id) *id=query.value(0).toInt(&ok);
        return true && ok;
    }
    return false;
}




QStringList JKHADatabase::getPayers() const
{
    QStringList cats;
    QSqlQuery query(m_db);
    auto finalyact=jkfinally(std::bind(&debugLogQueryResult, query, "getPayers"));
    query.exec(QString("SELECT name FROM payers"));
    if (query.isActive() && query.next()) {
        bool ok=query.first();
        while (ok) {
            cats<<query.value(0).toString();
            ok=query.next();
        }
    }
    return cats;
}


int JKHADatabase::ensurePayer(const QString &name)
{
    int id=-1;
    if (hasPayer(name, &id)) return id;
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO payers (id, name) VALUES (null, :name)");
    query.bindValue(":name", name);
    query.exec();
    debugLogQueryResult(query, "ensurePayer");
    refreshPayerModel();
    if (hasPayer(name, &id)) return id;
    throw std::runtime_error("unable to add payer");
}

bool JKHADatabase::hasPayer(const QString &name, int *id) const
{
    QSqlQuery query(m_db);
    query.exec(QString("SELECT id FROM payers WHERE name=='%1'").arg(name));
    auto finalyact=jkfinally(std::bind(&debugLogQueryResult, query, "hasPayer"));
    if (query.isActive() && query.next()) {
        bool ok=true;
        if (id) *id=query.value(0).toInt(&ok);
        return true && ok;
    }
    return false;
}

void JKHADatabase::debugLogQueryResult(QSqlQuery &q, const QString& name)
{
    qDebug()<<"-- UPDATE QUERY "<<name<<" ---";
    qDebug()<<"--   lastQuery: "<<q.lastQuery();
    qDebug()<<"--   isActive:  "<<q.isActive();
    qDebug()<<"--   isValid:   "<<q.isValid();
    if (q.isActive()) {
        auto r=q.record();
        qDebug()<<"--   columns:   "<<r.count();
        QString rec;
        for (int i=0; i<r.count(); i++) {
            if (rec.size()>0) rec+", ";
            rec+=(r.field(i).name()+"='"+r.value(i).toString()+"'");
        }
        qDebug()<<"--   record:    "<<rec;
    }
    qDebug()<<"--   lasterror: "<<q.lastError();
    qDebug()<<"----------------------------------------------------------------------------------------";
}


QVariant JKHADatabase::getDBProperty(const QString &property, const QVariant& defaultVal) const
{
    QSqlQuery query(m_db);
    query.exec(QString("SELECT value,type FROM settings WHERE key=='%1'").arg(property));
    auto finalyact=jkfinally(std::bind(&debugLogQueryResult, query, "getDBProperty"));
    if (query.isActive() && query.next()) {
        QString val=query.value(0).toString();
        QString type=query.value(1).toString().toLower().trimmed();
        bool ok=false;
        if (type=="int") {
            const auto v=val.toInt(&ok);
            if (ok) return QVariant(v);
            else return QVariant();
        } else if (type=="float" || type=="double") {
            const auto v=val.toDouble(&ok);
            if (ok) return QVariant(v);
            else return QVariant();
        } else if (type=="bool") {
            return (val.toLower().trimmed()=="true") || (val.toLower().trimmed()=="1") || (val.toLower().trimmed()=="yes");
        } else if (type=="string") {
            return QVariant(val);
        } else {
            return defaultVal;
        }
    }
    else return defaultVal;
}

int JKHADatabase::getDBPropertyInt(const QString &property, int defaultVal) const
{
    const QVariant v=getDBProperty(property);
    bool ok=false;
    if (v.type()==QVariant::Int) {
        auto vv=v.toInt(&ok);
        if (ok) return vv;
    }
    return defaultVal;
}

bool JKHADatabase::getDBPropertyBool(const QString &property, bool defaultVal) const
{
    const QVariant v=getDBProperty(property);
    if (v.type()==QVariant::Bool) {
        return v.toBool();
    }
    return defaultVal;
}

double JKHADatabase::getDBPropertyDouble(const QString &property, double defaultVal) const
{
    const QVariant v=getDBProperty(property);
    bool ok=false;
    if (v.type()==QVariant::Double) {
        auto vv=v.toDouble(&ok);
        if (ok) return vv;
    }
    return defaultVal;
}

QString JKHADatabase::getDBPropertyString(const QString &property, const QString &defaultVal) const
{
    const QVariant v=getDBProperty(property);
    if (v.type()==QVariant::String) {
        return v.toString();
    }
    return defaultVal;
}

void JKHADatabase::setDBProperty(const QString &property, double value)
{
    setDBProperty(property, QVariant(value));
}

void JKHADatabase::setDBProperty(const QString &property, bool value)
{
    setDBProperty(property, QVariant(value));
}

void JKHADatabase::setDBProperty(const QString &property, int value)
{
    setDBProperty(property, QVariant(value));
}

void JKHADatabase::setDBProperty(const QString &property, const QString &value)
{
    setDBProperty(property, QVariant(value));
}

void JKHADatabase::setDBProperty(const QString &property, const char *value)
{
    setDBProperty(property, QVariant(QString(value)));
}

void JKHADatabase::setDBProperty(const QString &property, const QVariant &value)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO settings (key, value, type)"
                  " VALUES (:key, :value, :type)");
    query.bindValue(":key", property);
    if (value.type()==QVariant::Bool) {
        query.bindValue(":value", value.toBool());
        query.bindValue(":type", "bool");
    } else if (value.type()==QVariant::Int) {
        query.bindValue(":value", value.toInt());
        query.bindValue(":type", "int");
    } else if (value.type()==QVariant::Double) {
        query.bindValue(":value", value.toDouble());
        query.bindValue(":type", "double");
    } else {
        query.bindValue(":value", value.toString());
        query.bindValue(":type", "string");
    }

    query.exec();
    debugLogQueryResult(query, "setDBProperty");

}

void JKHADatabase::refreshCategoriesModel()
{
    auto res=m_categoriesModel->select();
    qDebug()<<"-- UPDATE QUERY refreshCategoriesModel ---";
    qDebug()<<"--   lastQuery: "<<m_categoriesModel->query().lastQuery();
    qDebug()<<"--   select:    "<<res;
    qDebug()<<"--   lasterror: "<<m_categoriesModel->lastError();
    qDebug()<<"----------------------------------------------------------------------------------------";
}

void JKHADatabase::refreshExpensesModel()
{
    auto res=m_overviewModel->select();
    qDebug()<<"-- UPDATE QUERY refreshExpensesModel ---";
    qDebug()<<"--   lastQuery: "<<m_overviewModel->query().lastQuery();
    qDebug()<<"--   select:    "<<res;
    qDebug()<<"--   lasterror: "<<m_overviewModel->lastError();
    qDebug()<<"----------------------------------------------------------------------------------------";
}

void JKHADatabase::refreshPayeeModel()
{
    auto res=m_payeeModel->select();
    qDebug()<<"-- UPDATE QUERY refreshPayeeModel ---";
    qDebug()<<"--   lastQuery: "<<m_payeeModel->query().lastQuery();
    qDebug()<<"--   select:    "<<res;
    qDebug()<<"--   lasterror: "<<m_payeeModel->lastError();
    qDebug()<<"----------------------------------------------------------------------------------------";
}

void JKHADatabase::refreshPayerModel()
{
    auto res=m_payerModel->select();
    qDebug()<<"-- UPDATE QUERY refreshPayerModel ---";
    qDebug()<<"--   lastQuery: "<<m_payerModel->query().lastQuery();
    qDebug()<<"--   select:    "<<res;
    qDebug()<<"--   lasterror: "<<m_payerModel->lastError();
    qDebug()<<"----------------------------------------------------------------------------------------";
}

void JKHADatabase::refreshBudgetsModel()
{
    auto res=m_budgetsModel->select();
    qDebug()<<"-- UPDATE QUERY refreshBudgetsModel ---";
    qDebug()<<"--   lastQuery: "<<m_budgetsModel->query().lastQuery();
    qDebug()<<"--   select:    "<<res;
    qDebug()<<"--   lasterror: "<<m_budgetsModel->lastError();
    qDebug()<<"----------------------------------------------------------------------------------------";
}

void JKHADatabase::refreshRecurringExpensesModel()
{
    auto res=m_recurringExpensesModel->select();
    qDebug()<<"-- UPDATE QUERY refreshRecurringExpensesModel ---";
    qDebug()<<"--   lastQuery: "<<m_recurringExpensesModel->query().lastQuery();
    qDebug()<<"--   select:    "<<res;
    qDebug()<<"--   lasterror: "<<m_recurringExpensesModel->lastError();
    qDebug()<<"----------------------------------------------------------------------------------------";
}

void JKHADatabase::refreshValueablesModel()
{
    auto res=m_valueablesModel->select();
    qDebug()<<"-- UPDATE QUERY refreshValueablesModel ---";
    qDebug()<<"--   lastQuery: "<<m_valueablesModel->query().lastQuery();
    qDebug()<<"--   select:    "<<res;
    qDebug()<<"--   lasterror: "<<m_valueablesModel->lastError();
    qDebug()<<"----------------------------------------------------------------------------------------";
}

void JKHADatabase::refreshModels()
{
    refreshExpensesModel();
    refreshCategoriesModel();
    refreshPayeeModel();
    refreshPayerModel();
    refreshBudgetsModel();
    refreshRecurringExpensesModel();
    refreshValueablesModel();
}

void JKHADatabase::createModels()
{
    int i;

    if (m_overviewModel) delete m_overviewModel;

    m_overviewModel=new QSqlRelationalTableModel(this, m_db);

    m_overviewModel->setTable("expenses");
    m_overviewModel->setRelation(2, QSqlRelation("payees", "id", "name"));
    m_overviewModel->setRelation(3, QSqlRelation("payers", "id", "name"));
    m_overviewModel->setRelation(5, QSqlRelation("categories", "id", "name"));
    m_overviewModel->setEditStrategy(QSqlRelationalTableModel::EditStrategy::OnRowChange);
    m_overviewModel->setSort(1, Qt::AscendingOrder);
    i=0;
    m_overviewModel->setHeaderData(i, Qt::Horizontal, QObject::tr("ID")); i++;
    m_overviewModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Date")); i++;
    m_overviewModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Payee")); i++;
    m_overviewModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Payer")); i++;
    m_overviewModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Amount")); i++;
    m_overviewModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Category")); i++;
    m_overviewModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Description")); i++;



    if (m_categoriesModel) delete m_categoriesModel;

    m_categoriesModel=new QSqlTableModel(this, m_db);

    m_categoriesModel->setTable("categories");
    m_categoriesModel->setEditStrategy(QSqlTableModel::EditStrategy::OnRowChange);
    m_categoriesModel->setSort(1, Qt::AscendingOrder);
    i=0;
    m_categoriesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("ID")); i++;
    m_categoriesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Category Name")); i++;



    if (m_payeeModel) delete m_payeeModel;

    m_payeeModel=new QSqlTableModel(this, m_db);

    m_payeeModel->setTable("payees");
    m_payeeModel->setEditStrategy(QSqlTableModel::EditStrategy::OnRowChange);
    m_payeeModel->setSort(1, Qt::AscendingOrder);
    i=0;
    m_payeeModel->setHeaderData(i, Qt::Horizontal, QObject::tr("ID")); i++;
    m_payeeModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Payee Name")); i++;



    if (m_payerModel) delete m_payerModel;

    m_payerModel=new QSqlTableModel(this, m_db);

    m_payerModel->setTable("payers");
    m_payerModel->setEditStrategy(QSqlTableModel::EditStrategy::OnRowChange);
    m_payerModel->setSort(1, Qt::AscendingOrder);
    i=0;
    m_payerModel->setHeaderData(i, Qt::Horizontal, QObject::tr("ID")); i++;
    m_payerModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Payer Name")); i++;



    if (m_budgetsModel) delete m_budgetsModel;

    m_budgetsModel=new QSqlTableModel(this, m_db);

    m_budgetsModel->setTable("budgets");
    m_budgetsModel->setEditStrategy(QSqlTableModel::EditStrategy::OnRowChange);
    m_budgetsModel->setSort(1, Qt::AscendingOrder);
    i=0;
    m_budgetsModel->setHeaderData(i, Qt::Horizontal, QObject::tr("ID")); i++;
    m_budgetsModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Added")); i++;
    m_budgetsModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Name")); i++;
    m_budgetsModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Description")); i++;



    if (m_recurringExpensesModel) delete m_recurringExpensesModel;

    m_recurringExpensesModel=new QSqlRelationalTableModel(this, m_db);

    m_recurringExpensesModel->setTable("recurringExpenses");
    m_recurringExpensesModel->setRelation(4, QSqlRelation("payees", "id", "name"));
    m_recurringExpensesModel->setRelation(5, QSqlRelation("payers", "id", "name"));
    m_recurringExpensesModel->setRelation(7, QSqlRelation("categories", "id", "name"));
    m_recurringExpensesModel->setEditStrategy(QSqlTableModel::EditStrategy::OnRowChange);
    m_recurringExpensesModel->setSort(1, Qt::AscendingOrder);
    i=0;
    m_recurringExpensesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("ID")); i++;
    m_recurringExpensesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Start Date")); i++;
    m_recurringExpensesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Repeat Mode")); i++;
    m_recurringExpensesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Last Executed")); i++;
    m_recurringExpensesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Payee")); i++;
    m_recurringExpensesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Payer")); i++;
    m_recurringExpensesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Amount")); i++;
    m_recurringExpensesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Category")); i++;
    m_recurringExpensesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Description")); i++;



    if (m_valueablesModel) delete m_valueablesModel;

    m_valueablesModel=new QSqlRelationalTableModel(this, m_db);

    m_valueablesModel->setTable("valuables");
    m_valueablesModel->setRelation(6, QSqlRelation("payers", "id", "name"));
    m_valueablesModel->setEditStrategy(QSqlTableModel::EditStrategy::OnRowChange);
    m_valueablesModel->setSort(1, Qt::AscendingOrder);
    i=0;
    m_valueablesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("ID")); i++;
    m_valueablesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Added Date")); i++;
    m_valueablesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Name")); i++;
    m_valueablesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Value")); i++;
    m_valueablesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Category")); i++;
    m_valueablesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Description")); i++;
    m_valueablesModel->setHeaderData(i, Qt::Horizontal, QObject::tr("Payer")); i++;

    refreshModels();

}

QString JKHABudgetType2String(JKHABudgetType type)
{
    switch(type) {
        case JKHABudgetType::Monthly: return "MonthlyBudget";
        case JKHABudgetType::Yearly: return "Yearly Budget";
    }
    throw std::runtime_error("unknown JKHABudgetType in JKHABudgetType2String()");
}

QString JKHABudgetType2LocalString(JKHABudgetType type)
{
    switch(type) {
        case JKHABudgetType::Monthly: return QObject::tr("Monthly Budget");
        case JKHABudgetType::Yearly: return QObject::tr("Yearly Budget");
    }
    throw std::runtime_error("unknown JKHABudgetType in JKHABudgetType2LocalString()");
}
