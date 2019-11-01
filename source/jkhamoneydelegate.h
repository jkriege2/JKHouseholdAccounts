#ifndef JKHAMONEYDELEGATE_H
#define JKHAMONEYDELEGATE_H


#include <QStyledItemDelegate>

class JKHADatabase; // forward

class JKHAMoneyDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    JKHAMoneyDelegate(JKHADatabase* database, QObject *parent = nullptr, bool negativeAlowed=true);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual QString displayText(const QVariant &value, const QLocale &locale) const override;
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    JKHADatabase* m_database;
    bool m_negativeAlowed;
};


#endif // JKHAMONEYDELEGATE_H
