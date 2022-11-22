#ifndef JKHACategoriesDELEGATE_H
#define JKHACategoriesDELEGATE_H

#include <QStyledItemDelegate>

class JKHADatabase; // forward

class JKHACategoriesDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    JKHACategoriesDelegate(JKHADatabase* database, QObject *parent = nullptr);


    virtual QString displayText(const QVariant &value, const QLocale &locale) const override;
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    JKHADatabase* m_database;
};

#endif // JKHACategoriesDELEGATE_H
