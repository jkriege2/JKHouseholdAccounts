#include "jktreecombobox.h"
#include <QHeaderView>

JKTreeComboBox::JKTreeComboBox(QWidget* parent):
    QComboBox(parent)
{
    m_view = new QTreeView;
    m_view->setFrameShape(QFrame::NoFrame);
    m_view->setEditTriggers(QTreeView::NoEditTriggers);
    m_view->setAlternatingRowColors(true);
    m_view->setSelectionBehavior(QTreeView::SelectRows);
    m_view->setRootIsDecorated(false);
    m_view->setWordWrap(true);
    m_view->setAllColumnsShowFocus(true);
    m_view->setItemsExpandable(false);
    setView(m_view);
    m_view->header()->setVisible(false);
}

JKTreeComboBox::~JKTreeComboBox()
{

}

void JKTreeComboBox::hideColumn(int n)
{
    m_view->hideColumn(n);
}

void JKTreeComboBox::expandAll()
{
    m_view->expandAll();
}

void JKTreeComboBox::selectIndex(const QModelIndex &index)
{
    setRootModelIndex(index.parent());
    setCurrentIndex(index.row());
    m_view->setCurrentIndex( index );
}

QModelIndex JKTreeComboBox::selectedTreeIndex() const
{
    return m_view->model()->index(currentIndex(),0,rootModelIndex());
}

void JKTreeComboBox::showPopup()
{
    setRootModelIndex(QModelIndex());
    QComboBox::showPopup();
}

void JKTreeComboBox::hidePopup()
{
    setRootModelIndex(m_view->currentIndex().parent());
    setCurrentIndex(  m_view->currentIndex().row());
    QComboBox::hidePopup();
}
