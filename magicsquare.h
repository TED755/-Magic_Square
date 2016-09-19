#ifndef MAGICSQUARE_H
#define MAGICSQUARE_H

#include <iostream>
#include <vector>
#include <ctime>
#include <QVariant>
#include <QAbstractTableModel>
#include <QDebug>
#include <QList>
#include <cmath>

using namespace std;

class MagicSquare
{

public:
    MagicSquare(int n, int c);
    void BuildSquare_odd(int n);
    void BuildSquare_even(int n);
    void BuildSquare4(vector<vector<int> > &matrix1, int n);
    void BuildSquare6(vector<vector<int> > &matrix1, int n);
    void build_version1();
    void build_version2();
    void build_version3();
    void build_version4();
    int size();
    bool CheckSquare(int n);
    bool CheckValue(int row, int col);
    int check_sum(int n);
    int check_num(int n);
    void Zero(int n);
    bool isFull(int n);
    int ItemsCount();

    int Rows()const {return matrix.size();}
    int Cols()const {return matrix[0].size();}

    QVariant Value (int row, int col) const
    {
        if(row >= 0 && row < matrix.size()
                && col >=0 && col <  matrix[0].size())
            return QVariant(matrix.at(row).at( col));

        else
            return QVariant();
    }

    void SetValue (int row, int col, int value);
    int itcount = 0;
    int complexity;
    bool flag = 0;
    QList<QPair <int, int>> saveposition;
    QList<int> numbers;
    QPair<int, int> save;


private:
    vector<vector<int>> matrix;
    vector<vector<int>> matrixcheck;

};

#endif // MAGICSQUARE

