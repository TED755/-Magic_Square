#include "magicsquare.h"
#include <QDebug>
#include <QList>

void MagicSquare::Zero(int n)
{
   QList<QPair<int, int> > indexies ;//= new QList<QPair<int, int> >();

   for(int i = 0; i < n; i++)
       for(int j = 0; j < n; j++)
       {
           indexies.push_back( QPair<int, int>(i,j));
       }


    int x = n;
    int randomInd;
    QPair<int, int> ind;
    srand(time(NULL));
    while (x > 0 && indexies.size() > 0){

        randomInd = rand() % indexies.size();
        ind = indexies[randomInd];
        matrix[ind.first][ind.second] = 0;
        x--;

        indexies.removeAt(randomInd);
    }
}

void MagicSquare::SetValue(int row, int col, int value)
{
    if(row >= 0 && row < matrix.size()
            && col >=0 && col <  matrix[0].size())
        if (value == matrixcheck[row][col])
            matrix[row][col] = value;

    else
        return;
}

bool MagicSquare::isFull(int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] != 0)
                return true;
}
