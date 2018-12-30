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


JKHADatabase::JKHADatabase(QObject *parent):
    QObject(parent), m_overviewModel(nullptr)
{
}

JKHADatabase::~JKHADatabase()
{
    delete m_overviewModel;
    m_overviewModel=nullptr;
    m_db.commit();
    m_db.close();
}

QSqlTableModel *JKHADatabase::getOverviewModel()
{
    return m_overviewModel;
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
        query.exec("create table expenses (id int primary key, "
                   "date date, payee varchar(200), amount money, description varchar(200))");
        qDebug()<<query.lastQuery()<<"\n  --> "<<query.lastError();
        query.exec("insert into expenses values(1, 'Dec-24-2018', 'REWE', 49.99, 'Wocheneinkauf')");
        qDebug()<<query.lastQuery()<<"\n  --> "<<query.lastError();
        query.exec("insert into expenses values(2, 'Dec-31-2018', 'REWE', 15.88, 'Wocheneinkauf')");
        qDebug()<<query.lastQuery()<<"\n  --> "<<query.lastError();
    }

    createModels();


}

void JKHADatabase::createModels()
{
    if (m_overviewModel) delete m_overviewModel;

    m_overviewModel=new QSqlTableModel(this, m_db);

    m_overviewModel->setTable("expenses");
    m_overviewModel->setEditStrategy(QSqlTableModel::OnRowChange);
    qDebug()<<m_overviewModel->select();
    qDebug()<<m_overviewModel->lastError();
    m_overviewModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m_overviewModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    m_overviewModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Payee"));
    m_overviewModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Amount"));
    m_overviewModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Description"));

}
