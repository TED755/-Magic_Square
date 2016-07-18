#include "magicsquare.h"
#include <QDebug>
#include <QList>

void MagicSquare::Zero(int n)
{
   QList<QPair<int, int>> indexies;

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
        //save = ind;

        saveposition.push_back(ind);

        x--;
        indexies.removeAt(randomInd);
    }
    for (int i = 0; i < matrix.size(); i++)
        for(int j = 0; j < matrix.size(); j++)
            if(matrix[i][j] == 0)
                Itcount++;
    qDebug()<<saveposition;
}

void MagicSquare::SetValue(int row, int col, int value)
{

    if(row >= 0 && row < matrix.size()
            && col >=0 && col <  matrix[0].size()){
        Itcount *= 0;
        for (int i = 0; i < matrix.size(); i++)
            for(int j = 0; j < matrix.size(); j++)
                if(matrix[i][j] == 0)
                    Itcount++;

        //       if (value == matrixcheck[row][col]){
        matrix[row][col] = value;
                    Itcount--;
    }
    //       }

    //else
    //   return;
}

bool MagicSquare::isFull(int n)
{
    qDebug() <<"Start check";
    for (int i = 0; i < n; i++){
        qDebug() << "enter for i";
        for (int j = 0; j < n; j++){
            qDebug() << "enter for j";
            if (matrix[i][j] != 0){
                qDebug()<<"returned";
                return true;

            }
        }
    }
}

int MagicSquare::ItemsCount()
{
    return Itcount;
}
