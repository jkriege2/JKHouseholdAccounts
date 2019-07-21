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

class JKHADatabase: public QObject {
    Q_OBJECT
public:
    JKHADatabase(QObject* parent);
    virtual ~JKHADatabase();

    QSqlTableModel *getOverviewModel();

    /** \brief create a new database, stored in the file \a filename */
    void createNew(const QString& filename);
    /** \brief add a new expense to the opened database */
    void addExpense(const QDate& date, double amount, const QString& payee, const QString& description, bool autorefresh=false);
    /** \brief read the current currency from the SETTINGS-table in the current database */
    QString getCurrency() const;

    void refreshModels();

protected:
    QSqlTableModel* m_overviewModel;
    QSqlDatabase m_db;
    QSqlQuery m_query;
    void createModels();
};


#endif // JKHADATABASETOOLS_H
