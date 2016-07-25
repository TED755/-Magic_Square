#include "magicsquare.h"

void MagicSquare::Zero(int n)
{
   QList<QPair<int, int>> indexies;

   int x;
   switch (complexity) {
   case 1:{
       qDebug()<<"Уровень сложности: 1";
       x = n;
       qDebug()<< x;
       break;
   }
   case 2:{
       qDebug()<<"Уровень сложности: 2";
       x = n + n*0.5;
       break;
   }
   case 3:{
       qDebug()<<"Уровень сложности: 3";
       x = n + n*0.9;
       break;
   }
   default:
       break;
   }
   for(int i = 0; i < n; i++)
       for(int j = 0; j < n; j++)
       {
           indexies.push_back( QPair<int, int>(i,j));
       }


    int randomInd;
    QPair<int, int> ind;
    srand(time(NULL));

    while (x > 0 && indexies.size() > 0){

        randomInd = rand() % indexies.size();
        ind = indexies[randomInd];
        matrix[ind.first][ind.second] = 0;

        saveposition.push_back(ind);

        x--;
        indexies.removeAt(randomInd);
    }
    for (int i = 0; i < matrix.size(); i++)
        for(int j = 0; j < matrix.size(); j++)
            if(matrix[i][j] == 0)
                itcount++;
    qDebug()<<saveposition;
}

void MagicSquare::SetValue(int row, int col, int value)
{
    int count;

    if(row >= 0 && row < matrix.size()
            && col >=0 && col <  matrix[0].size()){
        //itcount *= 0;
        //        for (int i = 0; i < matrix.size(); i++)
        //            for(int j = 0; j < matrix.size(); j++)
        //               if(matrix[i][j] == 0)
        //                    itcount++;


        matrix[row][col] = value;
        for (int i = 0; i < matrix.size(); i++)
            for(int j = 0; j < matrix.size(); j++)
               if(matrix[i][j] == 0)
                    count++;
        itcount = count;
        count = 0;
        //itcount--;

    }
    //       }

    //else
    //   return;
}

bool MagicSquare::CheckValue(int row, int col)
{
    if(matrix[row][col] == matrixcheck[row][col])
        return true;
    else
        return false;
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
    return itcount;
}

