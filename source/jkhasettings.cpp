#include "jkhasettings.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

JKHASettings::JKHASettings():
    QSettings(QSettings::UserScope, "jkrieger.de", "JKHouseholdAccounts")
{

}

void JKHASettings::setCurrentLanguage(const QString &language)
{
    setValue("language", language);
}

QString JKHASettings::getCurrentLanguage() const
{
    return value("language", "en").toString();
}
