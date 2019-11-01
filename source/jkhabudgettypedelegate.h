#ifndef JKHABUDGETTYPEDELEGATE_H
#define JKHABUDGETTYPEDELEGATE_H

#include <QStyledItemDelegate>

class JKHADatabase; // forward

class JKHABudgetTypeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    JKHABudgetTypeDelegate(JKHADatabase* database, QObject *parent = nullptr);


    virtual QString displayText(const QVariant &value, const QLocale &locale) const override;
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    JKHADatabase* m_database;
};

#endif // JKHABUDGETTYPEDELEGATE_H
