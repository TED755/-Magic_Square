#include "magicsquare.h"
#include "QDebug"

MagicSquare::MagicSquare(int n)
{
    srand(time(NULL));
    matrix.resize(n);
    for (int i = 0; i < matrix.size(); i++)
        matrix[i].resize(n);
    matrixcheck.resize(n);
    for (int i = 0; i < matrixcheck.size(); i++)
        matrixcheck[i].resize(n);
    if (n % 2 != 0)
        BuildSquare_odd(n);
    else BuildSquare_even(n);
    matrixcheck = matrix;
    Itcount = n;
}


void MagicSquare::BuildSquare_odd(int n)
{
    int row = 0, count = 0, column;
    column = n / 2;
    for (count = 1; count <= n*n; ++count){
        matrix[row][column] = count;
        row--;
        column++;
        if (count % n == 0){
            row += 2;
            column--;
        }
        else{
            if (column == n)
                column -= n;
            else if (row < 0)
                row += n;
        }
    }
}



void MagicSquare::BuildSquare_even(int n)
{
    int i, j, count = 0, row, column, sm = 0;
    bool even = false, cwise;
    vector < vector <int> > matrix1;
    matrix1.resize(2*n-2);
    for (i = 0; i < 2*n-2; i++)
        matrix1[i].resize(n);

    for (i = 0; i < 2*n-2; i++)
        for (j = 0; j < n; j++)
            matrix1[i][j] = 0;
    if (n % 4 == 0){}
    else
    {
        n -= 2;
        even = true;
    }
    cwise = true;
    while (sm + 1 < n)
    {
        if (cwise == true)
        {
            row = (n/2) - 1 + sm;
            column = 0;
            while (count%(2*n) != 1)
            {
                count = 1 + n * sm;
                matrix1[row][column] = count++;
                while (count%(n/2)!=1)
                {
                    row--;
                    column++;
                    matrix1[row][column] = count++;
                }
                matrix1[row][++column] = count++;
                while(count%(n/2) != 1)
                {
                    row++;
                    column++;
                    matrix1[row][column] = count++;
                }
                matrix1[++row][column] = count++;
                while(count%(n/2) != 1)
                {
                    row++;
                    column--;
                    matrix1[row][column] = count++;
                }
                matrix1[row][--column] = count++;
                while(count %(n/2) != 1)
                {
                    row--;
                    column--;
                    matrix1[row][column] = count++;
                }
                cwise = false;
            }
            sm += 2;
        }
        if(cwise == false)
        {
            row = (n/2) - 1 + sm;//начальные значения для непоч
            column = n - 1;
            while(count%(2*n) != 0)
            {
                matrix1[row][column] = count++;
                while(count%(n/2) != 1)
                {
                    row--;
                    column--;
                    matrix1[row][column] = count++;
                }
                matrix1[row][--column] = count++;
                while(count%(n/2) != 1)
                {
                    row++;
                    column--;
                    matrix1[row][column] = count++;
                }
                matrix1[++row][column] = count++;
                while (count%(n/2)!= 1)
                {
                    row++;
                    column++;
                    matrix1[row][column] = count++;
                }
                matrix1[row][++column] = count++;
                while(count%(n/2) != 1)
                {
                    row--;
                    column++;
                    matrix1[row][column] = count++;
                }
                count--;
                cwise = true;
            }
            sm += 2;
        }
    }
    qDebug()<<"build matrix1";
    if (n % 4 == 0 && even != true)
    {
        BuildSquare4(matrix1, n);
    }
    else
        BuildSquare6(matrix1, n);
}

void MagicSquare::BuildSquare4(vector<vector<int> > &matrix1, int n)
{
    int i,j;

    for (i = 0; i < n/2 - 1; i++)
        for(j = 0; j < n; j++)
        {
            if(matrix1[i][j] != 0)
                matrix1 [i+n][j] = matrix1[i][j];
        }
    for (i = n + n/2 - 1; i < 2*n - 2; i++)
        for (j = 0; j < n; j++)
        {
            if(matrix1[i][j]!= 0)
                matrix1[i-n][j] = matrix1[i][j];
        }
    qDebug()<<"copiyng start";
    int k;
    for (i = n/2 - 1, k = 0; i < n + n/2 - 1; i++, k++)
        for(j = 0; j < n; j++)
            matrix[k][j] = matrix1[i][j];//копирование матрицы
    qDebug()<<"copiyng finished";
}


void MagicSquare::BuildSquare6(vector<vector<int> > &matrix1, int n)
{
    n = n + 2;

    vector < vector <int> > matrix2;
    matrix2.resize(2*n-2);

    int i, j;

    for (i = 0; i < 2*n-2; i++)
        matrix2[i].resize(n);
    for(i = 1; i < n - 1; i++)
    {
        for(j = 1; j < n - 1; j++)
        {
            matrix2[i][j] = matrix1[i + (n-2)/2 - 2][j-1] + 2*(n - 1);   // add 2*(n-1)
        }
    }

    matrix2[0][0] =  3*(n/2) - 1;
    matrix2[0][n-1] = 1;
    matrix2[n-1][n-1] = n*n + 2 - (3*n)/2;
    matrix2[n-1][0] = n*n;

    i = 1;

    for(j = 1; j < n - 1; j++)                      //дополнение верхней строки
    {
        if (i <= n/2 - 2)
        {
            matrix2[0][j++] = 2*i + 1;
        }
        matrix2[0][j] = n*n + 1 - 2*i;
        i++;
    }

    matrix2[1][0] = n - 1;

    i = 1;

    int q = 1;

    for(j = 2; j < n - 1; j++)                       // левый столбец
    {
        while(i <= n/4)
        {
            matrix2[j++][0] = (3*n)/2 - 1 - i;
            i++;
        }
        i = 1;
        while(i <= n/4 + 1)
        {
            matrix2[j++][0] = n*n + 2 - 2*n + i;
            i++;
        }
        i = 1;
        while (i <= n/4 - 1)
        {
            matrix2[j++][0] = (3*n)/2 - 1 + q;
            matrix2[j][0] = n*n + 1 - n - q++;
            i++;
            j++;
        }
    }
    // добавление чисел в нижнюю строку и правый столбец
    for(j = 1; j < n - 1; j++)
        matrix2[n-1][j] = n*n + 1 - matrix2[0][j];  //комплементарные числа
    for(i = 1; i < n - 1; i++)
        matrix2[i][n-1] = n*n + 1 - matrix2[i][0];
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            matrix[i][j] = matrix2[i][j];
}
