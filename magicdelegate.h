#ifndef MAGICDELEGATE_H
#define MAGICDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>


class MagicDelegate : public QStyledItemDelegate
{
public:
    MagicDelegate();

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    // editing
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // MAGICDELEGATE_H
