/*

Warehouse Shelf Scanner: Rotate and Row-Sum

Ek warehouse mein shelf ki image ek N × N matrix hai, jisme har cell ek item count (0 se 99) hai. Aapko matrix ko pointers se process karna hai.

Tasks

1. Matrix Generation

Integer n input lo (2 ≤ n ≤ 5).
N × N random matrix banao, values 0 se 99 ke beech.
Matrix display karo.

2. Rotate 90° Clockwise

Pehle ek malloc se N × N matrix lo, aur rotated result ko doosre matrix mein pointer arithmetic se store karo. (Yahan in-place zaroori nahi hai.)
Pointer arithmetic use karo, matrix[i][j] allowed nahi.

3. Simple Filter

Rotated matrix ke har cell ko replace karo: cell ki value + uske right wale cell ki value ka average.
Last column ke cell ke liye right neighbor nahi hota, isliye uski value jaisi hai waisi hi rehne do.
Left se right jaate hue update karo, aur original (pehle wali) value hi use karo. Iske liye ek temporary variable prev kaafi hai.

4. Report

Final matrix ki har row ka sum print karo.
Constraints
2 ≤ N ≤ 5
0 ≤ cell value ≤ 99
Array indexing (a[i], a[i][j]) allowed nahi, sirf *(p + k) aur pointer increments.
Integer division use karo average ke liye.
Input Format
Enter matrix size (2-5):
Output Format
Original Matrix:
...
Matrix after 90° Clockwise Rotation:
...
Matrix after Filter:
...
Row Sums:
Row 1: <sum>
Row 2: <sum>
...
Sample (fixed matrix, logic check karne ke liye)

Original

10 20 30
40 50 60
70 80 90

Rotated 90° Clockwise

70 40 10
80 50 20
90 60 30

After Filter

55 25 10
65 35 20
75 45 30

Row Sums

Row 1: 90
Row 2: 120
Row 3: 150
Worked Example (Row 1 of rotated matrix: 70 40 10)
Cell	Value	Right Neighbor	Calculation	Result
1st	70	40	(70 + 40) / 2	55
2nd	40	10	(40 + 10) / 2	25
3rd	10	none	unchanged	10

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getSize(int *n)
{
    printf("Enter matrix size (2-5): ");

    if (scanf("%d", n) != 1)
    {
        printf("Error: Invalid input.\n");
        return 0;
    }

    if (*n < 2 || *n > 5)
    {
        printf("Error: Matrix size must be between 2 and 5.\n");
        return 0;
    }

    return 1;
}

void generateMatrix(int *matrix, int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            *(matrix + i * n + j) = rand() % 100;
        }
    }
}

void displayMatrix(int *matrix, int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d\t", *(matrix + i * n + j));
        }

        printf("\n");
    }
}

void rotateMatrix(int *original, int *rotated, int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            *(rotated + j * n + (n - 1 - i)) =
                *(original + i * n + j);
        }
    }
}

void applyFilter(int *matrix, int n)
{
    int i, j;
    int prev, current;

    for (i = 0; i < n; i++)
    {
        int *row = matrix + i * n;

        prev = *row;

        for (j = 0; j < n - 1; j++)
        {
            current = *(row + j + 1);

            *(row + j) = (prev + current) / 2;

            prev = current;
        }
    }
}

void print_row_sum(int *matrix, int n)
{
    int i, j;
    int sum;

    for (i = 0; i < n; i++)
    {
        sum = 0;

        int *row = matrix + i * n;

        for (j = 0; j < n; j++)
        {
            sum += *(row + j);
        }

        printf("Row %d: %d\n", i + 1, sum);
    }
}

int main()
{
    int n;

    if (!getSize(&n))
    {
        return 1;
    }

    srand((unsigned int)time(NULL));

    int *original = malloc(n * n * sizeof(int));

    if (original == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    int *rotated = malloc(n * n * sizeof(int));

    if (rotated == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        free(original);
        return 1;
    }

    generateMatrix(original, n);

    printf("\nOriginal Matrix:\n");
    displayMatrix(original, n);

    rotateMatrix(original, rotated, n);

    printf("\nMatrix after 90° Clockwise Rotation:\n");
    displayMatrix(rotated, n);

    applyFilter(rotated, n);

    printf("\nMatrix after Filter:\n");
    displayMatrix(rotated, n);

    printf("\nRow Sums:\n");
    print_row_sum(rotated, n);

    free(original);
    free(rotated);

    original = NULL;
    rotated = NULL;

    return 0;
}
