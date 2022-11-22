#include "jkhacategoriestreemodel.h"
#include "jkhadatabasetools.h"
#include <QApplication>


JKHACategoriesTreeModel::JKHACategoriesTreeModel(JKHADatabase *database_, QObject *parent):
    QAbstractItemModel(parent),
    database(database_)
{

}

JKHACategoriesTreeModel::~JKHACategoriesTreeModel()
{

}

QVariant JKHACategoriesTreeModel::data(const QModelIndex &index, int role) const
{
    if (!database) return QVariant();
    if (role == Qt::DisplayRole) {
        if (index.parent().isValid()) {
            return database->getSubCategories(index.parent().data().toString()).value(index.row(), "");
        } else {
            return database->getSuperCategories().value(index.row(), "");
        }
    } else if (role == Qt::UserRole) {
        if (index.parent().isValid()) {
            return database->getSubCategoryIDs(index.parent().data(Qt::DisplayRole).toString()).value(index.row(), -1);
        } else {
            return -1;
        }
    } else if (role == Qt::UserRole+1) {
        if (index.parent().isValid()) {
            return database->getSuperCategories().value(index.parent().row(), "");
        } else {
            return database->getSuperCategories().value(index.row(), "");
        }
    } else if (role == Qt::UserRole+2) {
        if (index.parent().isValid()) {
            return index.parent().data(Qt::DisplayRole).toString()+"/"+index.data(Qt::DisplayRole).toString();
        } else {
            return database->getSuperCategories().value(index.row(), "");
        }
    } else if (role==Qt::FontRole) {
        if (!index.parent().isValid()) {
            QFont f=QApplication::font();
            f.setBold(true);
            return f;
        }
    }
    return QVariant();
}

Qt::ItemFlags JKHACategoriesTreeModel::flags(const QModelIndex &index) const
{
    if (!database) return Qt::NoItemFlags;
    if (index.parent().isValid()) {
        return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
    } else {
        return Qt::ItemIsEnabled;
    }
}

QVariant JKHACategoriesTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (!database) return QVariant();
    if (role==Qt::DisplayRole) {
        if (section==0) return tr("Category");
    }
    return QVariant();
}

QModelIndex JKHACategoriesTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!database) return QModelIndex();
    if (parent.isValid()) return createIndex(row, 0, quintptr(1+parent.row()));
    else return createIndex(row, 0, quintptr(0));
}

QModelIndex JKHACategoriesTreeModel::index(const QString &cat) const
{
    if (!database) return QModelIndex();
    const auto splitCat=database->splitFullCategory(cat);
    const int superI=database->getSuperCategories().indexOf(splitCat.first);
    if (superI>=0) {
        const int subI=database->getSubCategories(splitCat.first).indexOf(splitCat.second);
        return index(subI,0,index(superI,0,QModelIndex()));
    }
    return QModelIndex();
}

QModelIndex JKHACategoriesTreeModel::parent(const QModelIndex &index) const
{
    if (!database) return QModelIndex();
    if (index.internalId()<=quintptr(0)) return QModelIndex();
    else return createIndex(index.internalId()-1,0,quintptr(0));
}

int JKHACategoriesTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!database) return 0;
    if (parent.isValid()) {
        if (parent.internalId()==0) {
            const QStringList sc= database->getSubCategories(parent.data().toString());
            return sc.size();
        }
    } else {
        const QStringList sc=  database->getSuperCategories();
        return sc.size();
    }
    return 0;
}

int JKHACategoriesTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

void JKHACategoriesTreeModel::resetModel()
{
    beginResetModel();
    endResetModel();
}
