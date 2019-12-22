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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>
#include "ui_main_window.h"
#include "jkhadatabasetools.h"

/**
 * Main window class for the application
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QMainWindow* parent = nullptr);

protected slots:
    void on_btnAddExpense_clicked();
    void on_actCategoryAdd_triggered();
    void on_actCategoryDelete_triggered();
    void on_actLanguageEnglish_triggered();
    void on_actLanguageGerman_triggered();
private:
    Ui::MainWindow ui;

    JKHADatabase* m_db;
};

#endif
