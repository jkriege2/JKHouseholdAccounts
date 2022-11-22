#ifndef JKHACATEGORIESTREEMODEL_H
#define JKHACATEGORIESTREEMODEL_H

#include <QAbstractItemModel>

class JKHADatabase; // forward

class JKHACategoriesTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum {
        CategoryIDRole=Qt::UserRole,
        SuperCategoryRole=Qt::UserRole+1,
        FullCategoryRole=Qt::UserRole+2
    };
    explicit JKHACategoriesTreeModel(JKHADatabase* database, QObject *parent = nullptr);
    virtual ~JKHACategoriesTreeModel();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex index(const QString& cat) const ;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void resetModel();

private:
    JKHADatabase* database;
};
#endif // JKHACATEGORIESTREEMODEL_H
