#include "jkhacategoriescombobox.h"
#include <QHeaderView>

JKHACategoriesComboBox::JKHACategoriesComboBox(QWidget* parent):
    QComboBox(parent)
{
    m_view = new QTreeView;
    m_view->setFrameShape(QFrame::NoFrame);
    m_view->setEditTriggers(QTreeView::NoEditTriggers);
    m_view->setAlternatingRowColors(true);
    m_view->setSelectionBehavior(QTreeView::SelectRows);
    m_view->setRootIsDecorated(false);
    m_view->setWordWrap(false);
    m_view->setAllColumnsShowFocus(true);
    m_view->setItemsExpandable(false);
    setView(m_view);
    m_view->header()->setVisible(false);
}

void JKHACategoriesComboBox::setDatabase(JKHADatabase *db)
{
    m_db=db;
    if (db) {
        m_view->setModel(db->getCategoriesTreeModel());
        setModel(db->getCategoriesTreeModel());
        expandAll();
    } else {
        setModel(nullptr);
        m_view->setModel(nullptr);
    }
}

void JKHACategoriesComboBox::setCurrentCategory(const QString &cat)
{
    if (m_db) {
        selectIndex(m_db->getCategoriesTreeModel()->index(cat));
    }
}

JKHACategoriesComboBox::~JKHACategoriesComboBox()
{

}

void JKHACategoriesComboBox::hideColumn(int n)
{
    m_view->hideColumn(n);
}

void JKHACategoriesComboBox::expandAll()
{
    m_view->expandAll();
}

void JKHACategoriesComboBox::selectIndex(const QModelIndex &index)
{
    setRootModelIndex(index.parent());
    setCurrentIndex(index.row());
    setCurrentText(index.data(JKHACategoriesTreeModel::FullCategoryRole).toString());
    setEditText(index.data(JKHACategoriesTreeModel::FullCategoryRole).toString());
    m_view->setCurrentIndex( index );
}

QModelIndex JKHACategoriesComboBox::selectedTreeIndex() const
{
    return m_view->model()->index(currentIndex(),0,rootModelIndex());
}

QString JKHACategoriesComboBox::currentCategory() const
{
    return currentText();
}

int JKHACategoriesComboBox::currentCategoryID() const
{
    const QString cat=currentCategory();
    return m_db->getCategoryID(cat);
}

void JKHACategoriesComboBox::showPopup()
{
    setRootModelIndex(QModelIndex());
    const QString txt=currentText();
    const QModelIndex idx=m_db->getCategoriesTreeModel()->index(txt);
    m_view->selectionModel()->select(idx, QItemSelectionModel::SelectCurrent);
    QComboBox::showPopup();
}

void JKHACategoriesComboBox::hidePopup()
{
    const QModelIndex idx=m_view->currentIndex();
    const QString txt=idx.data(JKHACategoriesTreeModel::FullCategoryRole).toString();
    const int row=  idx.row();
    const QModelIndex par=idx.parent();
    QComboBox::hidePopup();
    setRootModelIndex(par);
    setCurrentIndex(row);
    setCurrentText(txt);
    qDebug()<<"currText='"<<currentText()<<"', currentIndex="<<currentIndex()<<", par="<<rootModelIndex();
}
