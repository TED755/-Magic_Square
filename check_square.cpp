#include "magicsquare.h"

bool MagicSquare::CheckSquare(int n)
{
    if ((check_sum(n) == 1) && (check_num(n) == 1))
        return true;
    else return false;
}

int MagicSquare::check_sum(int n)
{
    int j;
    int sumGD = 0;
    for (int d = 0; d < n; d++)
        sumGD += matrix[d][d];
    int sumD = 0;
    for(int m = n-1, l = 0; m >= 0, l < n; m--, l++)
        sumD += matrix[m][l];
    int sumStr = 0;
    for (int i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            sumStr += matrix[i][j];
    int sumCol = 0;
    for (int i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            sumCol += matrix[i][j];
    sumStr /= n;
    sumCol /= n;
    if ((sumGD == sumStr) && (sumCol == sumGD)
            && (sumStr == sumCol) && (sumD == sumGD))
        return 1;
    else
        return 0;
}

int MagicSquare::check_num(int n)
{//check one that one time
    int *b;
    b = (int*)malloc(n*n *sizeof(int));
    for (int m = 0; m < n*n; m++)
        b[m] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (b[matrix[i][j] - 1] == 0)
                b[matrix[i][j] - 1]++;
            else return 0;
    return 1;

}
