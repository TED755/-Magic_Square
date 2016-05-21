#include "magicsquare.h"

bool MagicSquare::CheckSquare(int n)
{
    if ((check_sum(n) == 1) && (check_num(n) == 1))
        return true;
    else return false;
}

int MagicSquare::check_sum(int n)
{
    int sumD = 0;
    for (int d = 0; d < n; d++)
        sumD += matrix[d][d];
    int sumStr = 0;
    for (int i = 0; i < n; i++)
        sumStr += matrix[0][i];
    int sumCol = 0;
    for (int j = 0; j < n; j++)
        sumCol += matrix[j][0];
    if ((sumD == sumStr) && (sumCol == sumD) && (sumStr == sumCol))
        return 1;
    else
        return 0;
}

int MagicSquare::check_num(int n)
{//check one that one time
    vector <int> b;
    b.resize(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (b[matrix[i][j] - 1] == 0)
                b[matrix[i][j] - 1]++;
            else return 0;
    return 1;
}
