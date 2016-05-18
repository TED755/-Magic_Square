#include "magicdelegate.h"
#include "magicsquare.h"
#include <QSpinBox>

MagicDelegate::MagicDelegate()
{
    //int n;

}

void MagicDelegate::paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.data().toInt() == 0)
    {
        painter->setPen(Qt::red);
        painter->drawRect(QRect(option.rect.x() , option.rect.y() , 98, 28));
    }
    else
        QStyledItemDelegate::paint(painter, option,index);
}


QWidget * MagicDelegate::createEditor(QWidget *parent,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
       editor->setFrame(false);
       editor->setMinimum(1);
       editor->setMaximum(100);

       return editor;
}

void MagicDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(  index.data().toInt());
}

void MagicDelegate::setModelData(QWidget *editor,
                  QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->interpretText();
        int value = spinBox->value();

        model->setData(index, value, Qt::EditRole);
}

