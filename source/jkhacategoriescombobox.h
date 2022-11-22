#ifndef JKHACATEGORIESCOMBOBOX_H
#define JKHACATEGORIESCOMBOBOX_H

#include <QComboBox>
#include <QTreeView>
#include "jkhacategoriestreemodel.h"
#include "jkhadatabasetools.h"

class JKHACategoriesComboBox :public QComboBox
{
    Q_OBJECT
public:
    JKHACategoriesComboBox(QWidget* parent=nullptr);
    virtual ~JKHACategoriesComboBox();
    void showPopup() override;
    void hidePopup() override;
    void hideColumn(int n);
    void expandAll();
    void selectIndex(const QModelIndex &index);
    QModelIndex selectedTreeIndex() const;
    QString currentCategory() const;
    int currentCategoryID() const;
    void setDatabase(JKHADatabase* db);
public slots:
    void setCurrentCategory(const QString& cat);
private:
    QTreeView *m_view;
    JKHADatabase* m_db;
};

#endif // JKHACATEGORIESCOMBOBOX_H
