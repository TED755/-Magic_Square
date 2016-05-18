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
    m1 = sourceModel1;

    connect(m1, SIGNAL(dataChange(QModelIndex, QModelIndex)), this, SLOT(ChangeData(QModelIndex,QModelIndex)));
}

void MagicSquareModel::ChangeData(QModelIndex row, QModelIndex column)
{
    //QModelIndex r;
    //QModelIndex c;

    //emit dataChanged(r, c);
}

bool MagicSquareModel::setData(const QModelIndex &index, const QVariant &value, int role )
{}

Qt::ItemFlags MagicSquareModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;
    return  Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

