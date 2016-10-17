#ifndef SQUAREMODEL_H
#define SQUAREMODEL_H

#include "magicsquare.h"
#include <QAbstractTableModel>

class MagicSquareModel : public QAbstractTableModel
{
private:
    MagicSquare square;

public:
    MagicSquareModel(int n, int c) : square(n, c)
    {
        square.Zero(n);
        qDebug()<<square.numbers;
        modelnumbers = square.numbers;
    }

    bool Full (int n);
    int ItemsCountModel();
    bool CheckValueModel(int row, int col);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex())const override;

    QVariant data (const QModelIndex &ind, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    bool flag = true;

    void swap();
    int size();
    int numbersSize();

    QList<int> modelnumbers;

private:
    int row;
    int col;

};

#endif // MAGICSQUAREMODEL


