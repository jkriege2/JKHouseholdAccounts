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

#include "main_window.h"
#include <QToolBar>
#include "moc_main_window.cpp"
#include "defines.h"
#include "dlgaccountaddexpense.h"
#include "jkhasettings.h"
#include <QInputDialog>
#include <QMessageBox>

/**
 * Constructor
 */
MainWindow::MainWindow(QMainWindow* parent)
  : QMainWindow(parent)
{
    m_db=new JKHADatabase(this);

    m_db->createNew(".\\test.sqlite");


    this->ui.setupUi(this);
    this->ui.label->setText(QString(PROJECT_LONGNAME)+" "+QString(PROJECT_VERSION));
    this->ui.tbCategories->addAction(this->ui.actCategoryAdd);
    this->ui.tbCategories->addAction(this->ui.actCategoryDelete);
    m_db->assignOverviewTable(ui.tableExpenses);
    m_db->assignCategoriesTable(ui.tableCategories);
}

void MainWindow::on_btnAddExpense_clicked() {
    DlgAccountAddExpense dlg(m_db, this);
    dlg.exec();
}

void MainWindow::on_actCategoryAdd_triggered() {
    bool ok;
    const QString name = QInputDialog::getText(this, tr("Add Category"),
                                      tr("New Category:"), QLineEdit::Normal,
                                      tr("new category name"), &ok);
    if (ok && !name.isEmpty()) {
        m_db->ensureCategory(name);
    }
}

void MainWindow::on_actCategoryDelete_triggered()
{
    QModelIndexList lst=ui.tableCategories->selectionModel()->selectedRows(0);

    if (lst.size()>0) {
        const int ret = QMessageBox::warning(this, tr("Delete Categories"),
                                   tr("Do you really want to delete %1 categories?")+"\n\n"+
                                   tr("Note that deleting categories may invalidate you expenses list!"),
                                   QMessageBox::Yes | QMessageBox::No,
                                   QMessageBox::No);

        if (ret==QMessageBox::Yes) {
            QVector<int> catIDs;
            for (auto l: lst) {
                catIDs.push_back(l.data().toInt());
            }
            for (auto c: catIDs) {
                m_db->removeCategory(c);
            }

        }
    }
}

void MainWindow::on_actLanguageEnglish_triggered()
{
    JKHASettings set;
    set.setCurrentLanguage("en");
}

void MainWindow::on_actLanguageGerman_triggered()
{
    JKHASettings set;
    set.setCurrentLanguage("de");
}
