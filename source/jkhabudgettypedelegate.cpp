#include "jkhabudgettypedelegate.h"
#include "jkhadatabasetools.h"
#include <QComboBox>


JKHABudgetTypeDelegate::JKHABudgetTypeDelegate(JKHADatabase *database, QObject *parent)
    : QStyledItemDelegate(parent), m_database(database)
{
}

QString JKHABudgetTypeDelegate::displayText(const QVariant &value, const QLocale &/*locale*/) const
{
    JKHABudgetType bt=static_cast<JKHABudgetType>(value.toInt());
    return JKHABudgetType2LocalString(bt);
}


QWidget *JKHABudgetTypeDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &/* index */) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->setFrame(false);
    editor->addItem(JKHABudgetType2LocalString(static_cast<JKHABudgetType>(0)));
    editor->addItem(JKHABudgetType2LocalString(static_cast<JKHABudgetType>(1)));

    return editor;
}



void JKHABudgetTypeDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();

    QComboBox *realEditor = static_cast<QComboBox*>(editor);
    realEditor->setCurrentIndex(value);
}



void JKHABudgetTypeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QComboBox *realEditor = static_cast<QComboBox*>(editor);
    int value = realEditor->currentIndex();

    model->setData(index, value, Qt::EditRole);
}



void JKHABudgetTypeDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
