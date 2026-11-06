/*

1. Library Fine Management System

Design a console-based Library Fine Management System in C that tracks borrowed books and calculates late fines.

Requirements

Use a structure to store: Book ID, Title (single word), Borrower Name, Days Borrowed.
Allowed borrowing period is 14 days. Compute Late Days = Days Borrowed − 14 (if positive).
Calculate Fine using switch-case on a fine slab code derived from late days:
Late Days	Fine per Day
0	No fine
1–7	₹2
8–15	₹5
> 15	₹10
Display a Status: “On Time”, “Late”, or “Overdue” (late days > 15).
Print a warning pattern of ! characters equal to the slab level (Late: 1, Late 8-15: 2, Overdue: 3) using nested or simple loops.
If the book is returned on time, skip the pattern using continue.
Use functions for late days and fine calculation.
Use recursion to compute the total fine collected across all books.
Use a static variable inside a function to count how many books have fines.

Constraints: 1 ≤ N ≤ 100, 1 ≤ Days Borrowed ≤ 120.

Input Format

N
BookID Title BorrowerName DaysBorrowed

Sample Input

3
1 C_Basics Amit 10
2 DataStruct Priya 20
3 Algorithms Karan 40

Sample Output

Book ID: 1
Title: C_Basics
Borrower: Amit
Late Days: 0
Fine: 0
Status: On Time
Book ID: 2
Title: DataStruct
Borrower: Priya
Late Days: 6
Fine: 12
Status: Late
Warning: !
Book ID: 3
Title: Algorithms
Borrower: Karan
Late Days: 26
Fine: 260
Status: Overdue
Warning: !!!
Total Fine (via recursion): 272
Books with Fine (static counter): 2

*/

// code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define MAX_BOOKS 100

int totalBooksWithFine = 0;

struct Book
{
    int bookId;
    char title[50];
    char borrowerName[50];
    int daysBorrowed;
    int fine;
};

int readLine(const char *message, char *input, size_t size)
{
    printf("%s", message);

    if (fgets(input, size, stdin) == NULL)
    {
        printf("Error: Unable to read input.\n");
        return 0;
    }

    size_t len = strlen(input);

    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
        return 1;
    }

    int ch = getchar();

    if (ch == '\n' || ch == EOF)
        return 1;

    while (ch != '\n' && ch != EOF)
        ch = getchar();

    printf("Error: Input is too long.\n");
    return 0;
}

int readInt(const char *message, int min, int max, int *value)
{
    char input[100];
    char *endptr;
    long number;

    if (!readLine(message, input, sizeof(input)))
        return 0;

    errno = 0;
    number = strtol(input, &endptr, 10);

    if (input == endptr || errno == ERANGE)
    {
        printf("Error: Please enter a valid integer.\n");
        return 0;
    }

    while (isspace((unsigned char)*endptr))
        endptr++;

    if (*endptr != '\0' || number < INT_MIN || number > INT_MAX)
    {
        printf("Error: Please enter a valid integer.\n");
        return 0;
    }

    if (number < min || number > max)
    {
        printf("Error: Value must be between %d and %d.\n", min, max);
        return 0;
    }

    *value = (int)number;
    return 1;
}

int getBookDetails(struct Book *b)
{
    if (!readInt("Enter Book ID: ", 1, INT_MAX, &b->bookId))
        return 0;

    if (!readLine("Enter Book Title: ", b->title, sizeof(b->title)))
        return 0;

    if (b->title[0] == '\0')
    {
        printf("Error: Book title cannot be empty.\n");
        return 0;
    }

    if (!readLine("Enter Borrower Name: ",
                  b->borrowerName, sizeof(b->borrowerName)))
        return 0;

    if (b->borrowerName[0] == '\0')
    {
        printf("Error: Borrower name cannot be empty.\n");
        return 0;
    }

    if (!readInt("Enter Days Borrowed: ",
                 1, 120, &b->daysBorrowed))
        return 0;

    b->fine = 0;

    return 1;
}

int calculateLateDays(int daysBorrowed)
{
    if (daysBorrowed > 14)
        return daysBorrowed - 14;

    return 0;
}

int calculateFine(int lateDays)
{
    int slab_code;
    int fine_per_day;

    if (lateDays == 0)
        slab_code = 0;
    else if (lateDays <= 7)
        slab_code = 1;
    else if (lateDays <= 15)
        slab_code = 2;
    else
        slab_code = 3;

    switch (slab_code)
    {
    case 0:
        fine_per_day = 0;
        break;

    case 1:
        fine_per_day = 2;
        break;

    case 2:
        fine_per_day = 5;
        break;

    case 3:
        fine_per_day = 10;
        break;

    default:
        fine_per_day = 0;
    }

    return lateDays * fine_per_day;
}

char *getStatus(int lateDays)
{
    if (lateDays == 0)
        return "On Time";
    else if (lateDays > 15)
        return "Overdue";
    else
        return "Late";
}

int countBooksWithFine(int fine)
{
    static int count = 0;

    if (fine > 0)
        count++;

    return count;
}

void displayWarning(int lateDays)
{
    int level;

    if (lateDays <= 7)
        level = 1;
    else if (lateDays <= 15)
        level = 2;
    else
        level = 3;

    printf("\nWarning ");

    for (int i = 0; i < level; i++)
        printf("!");

    printf("\n");
}

void displayBook(struct Book *b, int lateDays)
{
    printf("Book ID: %d\n", b->bookId);
    printf("Title: %s\n", b->title);
    printf("Borrower: %s\n", b->borrowerName);
    printf("Late Days: %d\n", lateDays);
    printf("Fine: %d\n", b->fine);
    printf("Status: %s\n", getStatus(lateDays));
}

void processBooks(struct Book *books, int n)
{
    for (int i = 0; i < n; i++)
    {
        int lateDays = calculateLateDays((books + i)->daysBorrowed);

        (books + i)->fine = calculateFine(lateDays);

        totalBooksWithFine = countBooksWithFine((books + i)->fine);

        displayBook(books + i, lateDays);

        if (lateDays == 0)
        {
            printf("\n");
            continue;
        }

        displayWarning(lateDays);
        printf("\n");
    }
}

int calculateTotalFine(struct Book *books, int n)
{
    if (n == 0)
        return 0;

    return (books + n - 1)->fine +
           calculateTotalFine(books, n - 1);
}

int main()
{
    int n;

    if (!readInt("Enter number of books: ", 1, MAX_BOOKS, &n))
        return 1;

    struct Book *books = malloc(n * sizeof(struct Book));

    if (books == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter details of Book %d:\n", i + 1);

        if (!getBookDetails(books + i))
        {
            free(books);
            return 1;
        }
    }

    printf("\nLibrary Fine Report\n\n");

    processBooks(books, n);

    printf("Total Fine: %d\n", calculateTotalFine(books, n));

    printf("Books with Fine: %d\n",
           totalBooksWithFine);

    free(books);
    books = NULL;

    return 0;
}
