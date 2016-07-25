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

bool MagicSquareModel::setData(const QModelIndex &index, const QVariant &value, int role )
{
    flag = false;
    qDebug()<<"flag1: "<<flag;
    int row = index.row();
    int col = index.column();

    if( role == Qt::DisplayRole || role == Qt::EditRole){
        square.SetValue(row, col, value.toInt());
        if(square.CheckValue(row, col) == true){
            flag = true;
            //square.itcount--;
            qDebug()<<"flag2: "<<flag;
        }
        emit dataChanged(index, index);
        qDebug()<<"flag3: "<<flag;
        return true;
    }

    return false;
}

Qt::ItemFlags MagicSquareModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    for (int i = 0; i < square.saveposition.size(); i++)
        if (index.row() == square.saveposition[i].first && index.column() == square.saveposition[i].second){
            return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
            }

    return Qt::ItemIsEnabled | QAbstractItemModel::flags(index);
}

bool MagicSquareModel::Full(int n)
{
    if (square.isFull(n))
        if(square.CheckSquare(n) == true)
            return true;
        else return false;
    else return false;
}

int MagicSquareModel::ItemsCountModel()
{
    return square.ItemsCount();

}


