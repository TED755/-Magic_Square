#ifndef MAGICSQUARE_H
#define MAGICSQUARE_H

#include <iostream>
#include <vector>
#include <ctime>
#include <QVariant>

using namespace std;

class MagicSquare
{

public:
    MagicSquare(int n);
    void BuildSquare_odd(int n);
    void BuildSquare_even(int n);
    void BuildSquare4(vector<vector<long long> > &matrix1, int n);
    void BuildSquare6(vector<vector<long long> > & matrix1,int n);
    bool CheckSquare(int n);
    void Zero(int n);

    void print(int n);

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

    void SetValue (int row, int col, int value)
    {
        if(row >= 0 && row < matrix.size()
                && col >=0 && col <  matrix[0].size())
            matrix[row][col] = value;

        else
              return;
    }

private:
    vector < vector <int> > matrix;

};

#endif // MAGICSQUARE

