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
#include "moc_main_window.cpp"
#include "defines.h"
#include "dlgaccountaddexpense.h"

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
    m_db->assignOverviewTable(ui.tableExpenses);
    m_db->assignCategoriesTable(ui.tableCategories);
}

void MainWindow::on_btnAddExpense_clicked() {
    DlgAccountAddExpense dlg(m_db, this);
    dlg.exec();
}

void MainWindow::on_btnAddCategory_clicked() {
}
