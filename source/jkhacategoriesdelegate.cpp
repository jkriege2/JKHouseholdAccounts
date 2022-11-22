#include "jkhacategoriesdelegate.h"
#include "jkhadatabasetools.h"
#include "jktreecombobox.h"


JKHACategoriesDelegate::JKHACategoriesDelegate(JKHADatabase *database, QObject *parent)
    : QStyledItemDelegate(parent), m_database(database)
{
}

QString JKHACategoriesDelegate::displayText(const QVariant &value, const QLocale &/*locale*/) const
{
    /*JKHACategories bt=static_cast<JKHACategories>(value.toInt());
    return JKHACategories2LocalString(bt);*/
    return "";
}


QWidget *JKHACategoriesDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &/* index */) const
{
    JKTreeComboBox *editor = new JKTreeComboBox(parent);
    editor->setModel(m_database->getCategoriesTreeModel());
    editor->setFrame(false);
    return editor;
}



void JKHACategoriesDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    //const int value = index.model()->data(index, Qt::EditRole).toInt();
    const QString disp = index.data(Qt::DisplayRole).toString();

    JKTreeComboBox *realEditor = static_cast<JKTreeComboBox*>(editor);
    realEditor->setCurrentText(disp);
    realEditor->selectIndex(m_database->getCategoriesTreeModel()->index(disp));
}



void JKHACategoriesDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    JKTreeComboBox *realEditor = static_cast<JKTreeComboBox*>(editor);
    QModelIndex tidx = realEditor->selectedTreeIndex();
    bool ok=false;
    const int value=tidx.data(JKHACategoriesTreeModel::CategoryIDRole).toInt(&ok);
    if (ok) {
        model->setData(index, value, Qt::EditRole);
    }
}



void JKHACategoriesDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
