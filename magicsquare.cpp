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

    n % 2 != 0 ? BuildSquare_odd() : BuildSquare_even(n);

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
        build_version1();
        break;
    case 1:
        build_version2();
        break;
    case 2:
        build_version3();
        break;
    case 3:
        build_version4();
        break;
    case 4:
        build_version5();
        break;
    case 5:
        build_version6();
        break;
    case 6:
        build_version7();
        break;
    case 7:
        build_version8();
        break;
    default:
        break;
    }
}

void MagicSquare::build_version1()
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

void MagicSquare::build_version2()
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

void MagicSquare::build_version3()
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

void MagicSquare::build_version4()
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

void MagicSquare::build_version5()
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

void MagicSquare::build_version6()
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

void MagicSquare::build_version7()
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

void MagicSquare::build_version8()
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

void MagicSquare::BuildSquare_even(int n)
{
    srand(time(NULL));
    int i, j, count = 0, r, c, sm = 0;
    bool flag = false, cwise;
    vector < vector <int> > matrix1;
        matrix1.resize(2*n-2);
        for (i = 0; i < 2*n-2; i++)
            matrix1[i].resize(n);

    for (i = 0; i < 2*n-2; i++)//èíèöèàëèçàöèÿ åå íóëÿìè
        for (j = 0; j < n; j++)
            matrix1[i][j] = 0;

    if(n%4 == 2)          //äëÿ ïîñòðîåíèÿ ÷åòíî-÷åòíîãî ïîðÿäêà
    {             //ïåðâîíà÷àëüíî íóæíî ïîñòðîèòü n-2
        n = n - 2;
        flag = true;
    }

    if(n%4 == 0)    //ïîñòðîåíèå ÷åòíî-÷åòíîãî ïîðÿäêà ìåòîäîì êâàäðàòíûõ ðàìîê
    {
        cwise = true;              // íàïðàâëåíèå çàïîëíåíèÿ
        while (sm + 1 < n)    //ïîêà íå ïðîéäåì âñþ ìàòðèöó)  +2
        {
            if(cwise)//åñëè äâèæåíèå ïî ÷àñîâîé èñòèííî
            {
                r = (n/2) - 1 + sm; // ñòàðòîâûå çíà÷åíèÿ äëÿ ïî÷àñîâîé //ðÿä
                c = 0;//ñòîëáåö
                while(count%(2*n) != 1)//öèêë çàïîëíåíèÿ
                {//îñòàòîê îò äåëåíèÿ count íà óäâîåííûé ïîðÿäîê íå ðàâåí 1
                    count = 1+n*sm;//count ïðèñâàèâàåì íîâîå çíà÷åíèå
                    matrix1[r][c] = count++;//ìàòðèöå ýòî çíà÷åíèå +1
                    while(count%(n/2) != 1)//äàëåå â ÷åòûðåõ öèêëàõ
                    {
                        r--;//ïåðåìåùàåìñÿ ïî ìàòðèöå
                        c++;
                        matrix1[r][c] = count++;//çàïîëíÿÿ åå
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
                }//ïîñëå ïîñëåäåíåãî
                sm += 2;//óâåëè÷èâàåì sm íà 2
            }
            if(cwise == false)//åñëè äâèãàåìñÿ ïðîòèâ ÷àñîâîé
            {
                r =  (n/2) - 1 + sm;       // ñòàðòîâûå çíà÷åíèÿ äëÿ íåïî÷àñîâîé
                c = n - 1;
                while(count%(2*n)!= 0)
                {//âûïîëíÿåì îïåðàöèè çàïîëíåíèÿ äëÿ íåïî÷àñîâîé
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
        for(i = 0; i < n/2 - 1; i++)//âûïîëíÿåì ñäâèãè
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
            int k;//çàâåäåíèå îòäåëüíîãî ñ÷åò÷èêà
            for(i = n/2 - 1, k = 0; i < n + n/2 -1; i++, k++)
            {
                for(j = 0; j < n; j++)
                    matrix[k][j] = matrix1[i][j];//êîïèðîâàíèå ìàòðèöû
            }
        }
    }
    //ïîñòðîåíèå ÷åòíî-íå÷åòíîãî ïîðÿäêà
    if(n%4 == 0 && flag == true)
    {
        n += 2;//ïðèñâàèâàåì ïîðÿäêó èçíà÷àëüíîå çíà÷åíèå

        vector < vector <int> > matrix2;
        matrix2.resize(2*n-2);

        for (i = 0; i < 2*n-2; i++)
            matrix2[i].resize(n);

        for(i = 1; i < n - 1; i++)
        {
            for(j = 1; j < n - 1; j++)
            {
                matrix2[i][j] = matrix1[i + (n-2)/2 - 2][j-1] + 2*(n - 1);//äîáàâëåíèå 2*(n-1)
            }
        }

        matrix2[0][0] =  3*(n/2) - 1;
        matrix2[0][n-1] = 1;
        matrix2[n-1][n-1] = n*n + 2 - (3*n)/2;
        matrix2[n-1][0] = n*n;
        i = 1;

        for(j = 1; j < n - 1; j++)         //äîïîëíåíèå âåðõíåé ñòðîêè
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
        for(j = 2; j < n - 1; j++)                  // ëåâûé ñòîëáåö
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
        // äîáàâëåíèå ÷èñåë â íèæíþþ ñòðîêó è ïðàâûé ñòîëáåö
        for(j = 1; j < n - 1; j++)
            matrix2[n-1][j] = n*n + 1 - matrix2[0][j];  //êîìïëåìåíòàðíûå ÷èñëà

        for(i = 1; i < n - 1; i++)
            matrix2[i][n-1] = n*n + 1 - matrix2[i][0];

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                matrix[i][j] = matrix2[i][j];
    }
}
