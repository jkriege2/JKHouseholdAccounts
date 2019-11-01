#include "jkhamoneydelegate.h"
#include "jkhadatabasetools.h"
#include <QDoubleSpinBox>
#include <QPainter>
#include <QApplication>


JKHAMoneyDelegate::JKHAMoneyDelegate(JKHADatabase *database, QObject *parent, bool negativeAlowed)
    : QStyledItemDelegate(parent), m_database(database), m_negativeAlowed(negativeAlowed)
{
}

void JKHAMoneyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    opt.text.clear();
    opt.displayAlignment=Qt::AlignRight|Qt::AlignVCenter;

    QStyle* style = opt.widget ? opt.widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);

    QString text = displayText(index.data().toString(), QLocale::system());

    if (index.data().toDouble()<0) {
        painter->setPen(QColor("darkred"));
    } else {
        painter->setPen(QColor("darkgreen"));
    }
    opt.rect.adjust(5,0,-5,0);
    style->drawItemText(painter, opt.rect, opt.displayAlignment, opt.palette, true, text);

    painter->restore();
}

QString JKHAMoneyDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    return locale.toString(value.toDouble(), 'f', 2)+" "+m_database->getCurrency();
}

QWidget *JKHAMoneyDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &/* index */) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    if (m_negativeAlowed) editor->setMinimum(-10000000000);
    else editor->setMinimum(0);
    editor->setMaximum( 10000000000);
    editor->setDecimals(2);
    editor->setSuffix(" "+m_database->getCurrency());

    return editor;
}



void JKHAMoneyDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();

    QDoubleSpinBox *realEditor = static_cast<QDoubleSpinBox*>(editor);
    realEditor->setValue(value);
}



void JKHAMoneyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QDoubleSpinBox *realEditor = static_cast<QDoubleSpinBox*>(editor);
    realEditor->interpretText();
    double value = realEditor->value();

    model->setData(index, value, Qt::EditRole);
}



void JKHAMoneyDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
