#ifndef JKHASETTINGS_H
#define JKHASETTINGS_H

#include <QSettings>

class JKHASettings : public QSettings
{
public:
    JKHASettings();

    QString getCurrentLanguage() const;
    void setCurrentLanguage(const QString& language);
};

#endif // JKHASETTINGS_H
