#include "magicsquare.h"

MagicSquare::MagicSquare(int n, int c)
{
    srand(time(NULL));
    matrix.resize(n);
    for (int i = 0; i < matrix.size(); i++)
        matrix[i].resize(n);
    matrixcheck.resize(n);
    for (int i = 0; i < matrixcheck.size(); i++)
        matrixcheck[i].resize(n);

    n % 2 != 0 ? BuildSquare_odd() : BuildSquare_even();

    matrixcheck = matrix;
    itcount = 0;
    complexity = c;
}

int MagicSquare::size()
{
    return matrix.size();
}

void MagicSquare::BuildSquare_odd()
{
    int x;
    x = rand()%8;
    switch (x) {
    case 0:
        build_odd1();
        break;
    case 1:
        build_odd2();
        break;
    case 2:
        build_odd3();
        break;
    case 3:
        build_odd4();
        break;
    case 4:
        build_odd5();
        break;
    case 5:
        build_odd6();
        break;
    case 6:
        build_odd7();
        break;
    case 7:
        build_odd8();
        break;
    default:
        break;
    }
}

void MagicSquare::build_odd1()
{
    int row = 0, count = 0, column, n;
    n = matrix.size();
    column = n/2;
    for(count = 1; count <= n*n; ++count){
        matrix[row][column] = count;
        row--;
        column++;
        if(count % n == 0){
            row += 2;
            column--;
        }
        else{
            if(column == n)
                column -= n;
            else if(row < 0)
                row += n;
        }
    }
}

void MagicSquare::build_odd2()
{
    int row, count = 0, column, n;
    n = matrix.size();
    row = n/2;
    column = n - 1;

    for(count = 1; count <= n*n; ++count){
        matrix[row][column] = count;
        row--;
        column++;
        if(count % n == 0){
            row++;
            column-=2;
        }
        else{
            if(column == n)
                column-=n;
            else if(row < 0)
                row+=n;
        }
    }
}

void MagicSquare::build_odd3()
{
    int n, row = 0, count = 0, column;
    n = matrix.size();
    row = n/2;
    column = 0;
    for (count = 1; count <= n*n; ++count){
        matrix[row][column] = count;
        row++;
        column--;
        if (count % n == 0){
            column += 2;
            row--;
        }
        else{
            if (row == n)
                row -= n;
            else if (column < 0)
                column += n;
        }
    }
}

void MagicSquare::build_odd4()
{
    int n, row, column, count;
    n = matrix.size();
    row = n-1;
    column = n/2;

    for(count = 1; count <= n*n; ++count){
        matrix[row][column] = count;
        row++;
        column--;
        if(count % n == 0){
            row -= 2;
            column++;
        }
        else{
            if (row == n)
                row -= n;
            else if (column < 0)
                column += n;
        }
    }
}

void MagicSquare::build_odd5()
{
    int n, row, count = 0, column;
    n = matrix.size();
    row = n/2;
    column = n-1;

    for(count = 1; count <= n*n; ++count){
        matrix[row][column] = count;
        row++;
        column++;
        if(count % n == 0){
            column -= 2;
            row--;
        }
        else{
            if(row == n)
                row -= n;
            else if(column == n)
                column -= n;
        }
    }
}

void MagicSquare::build_odd6()
{
    int n, row, column, count;
    n = matrix.size();
    row = n - 1;
    column = n/2;

    for(count = 1; count <= n*n; ++count){
        matrix[row][column] = count;
        row++;
        column++;
        if(count % n == 0){
            row -= 2;
            column--;
        }
        else{
            if(row == n)
                row -= n;
            else if(column == n)
                column -= n;
        }
    }
}

void MagicSquare::build_odd7()
{
    int n, row, column = 0, count;
    n = matrix.size();
    row = n/2;

    for(count =  1; count <= n*n; ++count){
        matrix[row][column] = count;
        row--;
        column--;
        if(count % n == 0){
            row++;
            column +=2;
        }
        else{
            if(row < 0)
                row += n;
            else if(column < 0)
                column += n;
        }
    }
}

void MagicSquare::build_odd8()
{
    int n, row = 0, column, count = 0;
    n = matrix.size();
    column = n/2;

    for(count = 1; count <= n*n; ++count){
        matrix[row][column] = count;
        row--;
        column--;
        if(count % n == 0){
            row += 2;
            column++;
        }
        else{
            if(row < 0)
                row += n;
            else if(column < 0)
                column += n;
        }
    }
}

void MagicSquare::BuildSquare_even()
{
    srand(time(NULL));
    int x;
    build_even1();

    x = rand()%4;

    switch(x){
    case 0:
        break;
    case 1:
        build_even2();
        break;
    case 2:
        build_even3();
        break;
    case 3:
        build_even4();
        break;
    default:
        break;
    }
}
void MagicSquare::build_even1()
{
    int i, j, count = 0, r, c, sm = 0;
    bool flag = false, cwise;
    int n = matrix.size();
    vector<vector<int>> matrix1;
    matrix1.resize(2*n-2);//создание отдельной матрицы
    for (i = 0; i < 2*n-2; i++)
        matrix1[i].resize(n);

    for (i = 0; i < 2*n-2; i++)//инициализация ее нулями
        for (j = 0; j < n; j++)
            matrix1[i][j] = 0;

    if(n%4 == 2)          //для построения четно-четного порядка
    {             //первоначально нужно построить n-2
        n = n - 2;
        flag = true;
    }

    if(n%4 == 0)    //построение четно-четного порядка методом квадратных рамок
    {
        cwise = true;              // направление заполнения
        while (sm + 1 < n)    //пока не пройдем всю матрицу) +2
        {
            if(cwise)//если движение по часовой истинно
            {
                r = (n/2) - 1 + sm; // стартовые значения для почасовой //ряд
                c = 0;//столбец
                while(count%(2*n) != 1)//цикл заполнения
                {//остаток от деления count на удвоенный порядок не равен 1
                    count = 1+n*sm;//count присваиваем новое значение
                    matrix1[r][c] = count++;//матрице это значение +1
                    while(count%(n/2) != 1)//далее в четырех циклах
                    {
                        r--;//перемещаемся по матрице
                        c++;
                        matrix1[r][c] = count++;//заполняя ее
                    }
                    matrix1[r][++c] = count++;
                    while(count%(n/2) != 1)
                    {
                        r++;
                        c++;
                        matrix1[r][c] = count++;
                    }
                    matrix1[++r][c]= count++;
                    while(count%(n/2) != 1)
                    {
                        r++;
                        c--;
                        matrix1[r][c] = count++;
                    }
                    matrix1[r][--c] = count++;
                    while(count%(n/2) != 1)
                    {
                        r--;
                        c--;
                        matrix1[r][c] = count++;
                    }
                    cwise = false;
                }//после последенего
                sm += 2;//увеличиваем sm на 2
            }
            if(cwise == false)//если двигаемся против часовой
            {
                r =  (n/2) - 1 + sm;// стартовые значения для непочасовой
                c = n - 1;
                while(count%(2*n)!= 0)
                {//выполняем операции заполнения для непочасовой
                    matrix1[r][c] = count++;
                    while(count%(n/2) != 1)
                    {
                        r--;
                        c--;
                        matrix1[r][c] = count++;
                    }
                    matrix1[r][--c] = count++;
                    while(count%(n/2) != 1)
                    {
                        r++;
                        c--;
                        matrix1[r][c] = count++;
                    }
                    matrix1[++r][c]= count++;
                    while(count%(n/2) != 1)
                    {
                        r++;
                        c++;
                        matrix1[r][c] = count++;
                    }
                    matrix1[r][++c] = count++;
                    while(count%(n/2) != 1)
                    {
                        r--;
                        c++;
                        matrix1[r][c] = count++;
                    }
                    count -= 1;
                    cwise = true;
                }
                sm += 2;
            }
        }
        for(i = 0; i < n/2 - 1; i++)//выполняем сдвиги
            for(j = 0; j < n; j++)
            {
                if(matrix1[i][j]!= 0)
                    matrix1[i+n][j] = matrix1[i][j];
            }
        for(i = n + n/2 - 1; i < 2*n - 2; i++ )
            for(j = 0; j < n; j++)
            {
                if(matrix1[i][j]!= 0)
                    matrix1[i-n][j] = matrix1[i][j];
            }
        if (!flag)
        {
            int k;//заведение отдельного счетчика
            for(i = n/2 - 1, k = 0; i < n + n/2 -1; i++, k++)
            {
                for(j = 0; j < n; j++)
                    matrix[k][j] = matrix1[i][j];//копирование матрицы
            }
        }
    }
    //построение четно-нечетного порядка
    if(n%4 == 0 && flag == true)
    {
        n += 2;//присваиваем порядку изначальное значение
        vector < vector <int> > matrix2;
        matrix2.resize(2*n-2);

        for (i = 0; i < 2*n-2; i++)
            matrix2[i].resize(n);

        for(i = 1; i < n - 1; i++)
        {
            for(j = 1; j < n - 1; j++)
            {
                matrix2[i][j] = matrix1[i + (n-2)/2 - 2][j-1] + 2*(n - 1);//добавление 2*(n-1)
            }
        }

        matrix2[0][0] =  3*(n/2) - 1;
        matrix2[0][n-1] = 1;
        matrix2[n-1][n-1] = n*n + 2 - (3*n)/2;
        matrix2[n-1][0] = n*n;
        i = 1;

        for(j = 1; j < n - 1; j++)         //дополнение верхней строки
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
        for(j = 2; j < n - 1; j++)// левый столбец
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
        //добавление чисел в нижнюю строку и правый столбец
        for(j = 1; j < n - 1; j++)
            matrix2[n-1][j] = n*n + 1 - matrix2[0][j];  //комплементарные числа

        for(i = 1; i < n - 1; i++)
            matrix2[i][n-1] = n*n + 1 - matrix2[i][0];

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                matrix[i][j] = matrix2[i][j];
    }
}

void MagicSquare::build_even2()
{
    build_even1();
    int i, j, k;
    int n = matrix.size();
    for(i = 0; i < n; i++){
        k = 1;
        for(j = 0; j <= n/2; j++){
            int x;
            x = matrix[i][j];
            matrix[i][j] = matrix[i][n-k];
            matrix[i][n-k] = x;
            k++;
        }
    }
}

void MagicSquare::build_even3()
{
    build_even1();
    int i, j, k, n;
    n = matrix.size();
    for(i = 0; i < n; i++){
        k = 1;
        for(j = 0; j <= n/2; j++){
            int x;
            x = matrix[j][i];
            matrix[j][i] = matrix[n - k][i];
            matrix[n - k][i] = x;
            k++;
        }
    }
}

void MagicSquare::build_even4()
{
    build_even1();
    build_even2();
    int i, j, k, n;
    n = matrix.size();
    for(i = 0; i < n; i++){
        k = 1;
        for(j = 0; j <= n/2; j++){
            int x;
            x = matrix[j][i];
            matrix[j][i] = matrix[n - k][i];
            matrix[n - k][i] = x;
            k++;
        }
    }
}
