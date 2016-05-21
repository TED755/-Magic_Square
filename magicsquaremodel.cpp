#include "magicsquaremodel.h"

int MagicSquareModel::rowCount(const QModelIndex &parent) const
{
    return square.Rows();
}

int MagicSquareModel::columnCount(const QModelIndex &parent) const
{
     return square.Cols();
}

QVariant MagicSquareModel::data (const QModelIndex &ind, int role) const
{
    int row = ind.row();
    int col = ind.column();

    if( role == Qt::DisplayRole || role == Qt::EditRole)
        return square.Value(row, col);


      //  return QAbstractTableModel::data(ind, role);

    return QVariant();
}

void MagicSquareModel::setSourceModel1(QAbstractItemModel *sourceModel1)
{
   /* m1 = sourceModel1;

    connect(m1, SIGNAL(dataChange(QModelIndex, QModelIndex)), this, SLOT(ChangeData(QModelIndex,QModelIndex)));*/
}

bool MagicSquareModel::setData(const QModelIndex &index, const QVariant &value, int role )
{
    int row = index.row();
    int col = index.column();

    if( role == Qt::DisplayRole || role == Qt::EditRole)
         square.SetValue(row, col, value.toInt());
}

Qt::ItemFlags MagicSquareModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    if( index.data() != 0) //TODO: create list af unlocked (equal to 0 at start) indexies (pair row, col)
        return QAbstractItemModel::flags(index);

    return  Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool MagicSquareModel::Full(int n)
{
    if (square.isFull(n))
        if(square.CheckSquare(n))
            return true;
}
