#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/*
sorted arrays
res: 1 2 3 4 5 6 7
pick: 2 3 4 5 6 7 8

command
curl localhost:4000/toto > text.txt | toto-sortedv2 < text.txt

*/

void print_entries(int **pick, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        printf("Entry %d: ", i);
        for (int j = 0; j < col; j++)
        {
            if (j != col - 1)
            {
                printf("%d, ", pick[i][j]);
            }
            else
            {
                printf("%d", pick[i][j]);
            }
        }
        printf("\n");
    }
}

int check(int *result, int **pick, int row)
{
    int hit = 0;
    int i = 0, j = 0;
    while (i < 7)
    {
        if (pick[row][j] > result[i])
        {
            i++;
        }
        if (pick[row][j] == result[i])
        {
            hit++;
            j++;
            i++;
        }
        if (pick[row][j] < result[i])
        {
            j++;
        }
    }
    return hit;
}

void process_winnings(int *result, int **pick, int row)
{
    int total_prize = 0;
    for (int i = 0; i < row; i++)
    {
        int hit = check(result, pick, i);
        if (hit > 2)
        {
            int prize = 0;
            if (hit == 3)
            {
                prize = 40;
            }
            else if (hit == 4)
            {
                prize = 85;
            }
            else if (hit == 5)
            {
                prize = 1000;
            }
            else if (hit == 6)
            {
                prize = 100000;
            }
            else if (hit == 7)
            {
                prize = 1000000;
            }
            total_prize += prize;

            printf("Entry %d Hits: %d Prize: %d\n", i, hit, prize);
        }
    }
    printf("Total Returns: %d\n", total_prize);
}

int main()
{
    clock_t begin = clock();
    printf("-----------------------TOTO CHECKER-------------------------------\n");
    printf("Key in the result\n");
    int col = 7;
    int result[7];
    int i = 0;
    while (i < col)
    {
        int num;
        int resp = scanf("%d", &num);
        if (resp == 1)
        {
            result[i] = num;
            i++;
        }
    }
    printf("Result is: \n");
    printf("###################################################################\n");
    for (int i = 0; i < col; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");
    int row;
    printf("\nKey in number of entries\n");
    printf("###################################################################\n");
    scanf("%d", &row);
    printf("Number of entries: %d\n", row);
    printf("###################################################################\n");
    int *pick[row];
    for (int i = 0; i < row; i++)
    {
        pick[i] = (int *)malloc(col * sizeof(int));
    }
    printf("\nKey in the entries\n");
    printf("###################################################################\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            scanf("%d", &pick[i][j]);
        }
    }
    print_entries(pick, row, col);
    printf("###################################################################\n");
    process_winnings(result, pick, row);

    for (int i = 0; i < row; i++)
    {
        free(pick[i]);
    }
    clock_t end = clock();

    printf("Elapsed: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);

    return 0;
}
