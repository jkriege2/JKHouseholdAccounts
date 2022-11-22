#ifndef JKTREECOMBOBOX_H
#define JKTREECOMBOBOX_H

#include <QComboBox>
#include <QTreeView>

class JKTreeComboBox :public QComboBox
{
    Q_OBJECT
public:
    JKTreeComboBox(QWidget* parent=nullptr);
    virtual ~JKTreeComboBox();
    void showPopup() override;
    void hidePopup() override;
    void hideColumn(int n);
    void expandAll();
    void selectIndex(const QModelIndex &index);
    QModelIndex selectedTreeIndex() const;
private:
    QTreeView *m_view;
};

#endif // JKTREECOMBOBOX_H
