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

#include <QApplication>
#include "main_window.h"
#include "defines.h"
#include "jkhasettings.h"

/**
 * Entry Point
 */
int main(int argc, char* argv[])
{
    QStringList paths=QCoreApplication::libraryPaths();
    paths.prepend("./");
    paths.prepend("./plugins/");
    paths.prepend(QFileInfo(argv[0]).dir().absolutePath());
    paths.prepend(QFileInfo(argv[0]).dir().absolutePath()+"/plugins/");
    QApplication app(argc, argv);
    app.setApplicationDisplayName(PROJECT_LONGNAME);
    app.setApplicationName(PROJECT_LONGNAME);
    app.setApplicationVersion(PROJECT_VERSION);

    JKHASettings set;
    QTranslator translator, translatorbase;
    //qDebug()<<QFileInfo(argv[0]).dir().absolutePath()+"/translations/jkhouseholdaccounts_de.qm"<<": "<<QFile(QFileInfo(argv[0]).dir().absolutePath()+"/translations/jkhouseholdaccounts_de.qm").exists();
    qDebug()<<"load "<<"jkhouseholdaccounts_" + set.getCurrentLanguage()<<": "<<
              translator.load("jkhouseholdaccounts_" + set.getCurrentLanguage(), QFileInfo(argv[0]).dir().absolutePath()+"/translations/");
    qDebug()<<"load "<<"qt_"+set.getCurrentLanguage()<<": "<<
              translatorbase.load("qt_"+set.getCurrentLanguage(), QFileInfo(argv[0]).dir().absolutePath()+"/translations/");
    app.installTranslator(&translator);
    app.installTranslator(&translatorbase);

    MainWindow mainWindow;

    mainWindow.show();

    return app.exec();
}
