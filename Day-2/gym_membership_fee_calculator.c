/*

4. Gym Membership Fee Calculator

Design a console-based program in C for a gym front desk. The program should accept member details, calculate the membership cost, and apply a tiered discount based on the plan duration.

Requirements

Read the member name, number of months, and plan type from the user.
Support three plans: Basic, Standard, and Premium. The user enters 1, 2, or 3.
Declare the monthly fees and the joining fee as constants: Basic = 800, Standard = 1200, Premium = 2000, and Joining Fee = 500.
Use switch-case to select the monthly fee.
Calculate Subtotal = months × monthly fee.
Use if-else if-else for a tiered discount:
12 or more months: 20% discount
6 to 11 months: 10% discount
Fewer than 6 months: no discount
Calculate Final Amount = Subtotal − Discount + Joining Fee. The joining fee is added after the discount and is never discounted.
Store the member details in a structure allocated with malloc, access it using a pointer, and release it with free.
Display an error message if the plan type or number of months is invalid.
Choice	Plan	Monthly Fee
1	Basic	800
2	Standard	1200
3	Premium	2000

Constraints: 1 ≤ Months ≤ 24, plan type must be 1, 2, or 3.

Input Format

Member name (single word)
Number of months
Plan type (1, 2, or 3)

Output Format

Member: <name>
Plan: <plan>
Months: <months>
Subtotal: <amount>
Discount: <amount>
Joining Fee: <amount>
Final Amount: <amount>

Sample Test Case 1

Input:
Kabir 6 3

Output:
Member: Kabir
Plan: Premium
Months: 6
Subtotal: 12000.00
Discount: 1200.00
Joining Fee: 500.00
Final Amount: 11300.00

Sample Test Case 2

Input:
Zoya 12 1

Output:
Member: Zoya
Plan: Basic
Months: 12
Subtotal: 9600.00
Discount: 1920.00
Joining Fee: 500.00
Final Amount: 8180.00

Sample Test Case 3 (invalid input)

Input:
Dev 30 2

Output:
Error: Invalid number of months.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define BASIC_PRICE 800
#define STANDARD_PRICE 1200
#define PREMIUM_PRICE 2000
#define JOINING_FEE 500

struct Member
{
    char name[100];
    int months;
    int plan_type;
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
    {
        return 1;
    }

    while (ch != '\n' && ch != EOF)
    {
        ch = getchar();
    }

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
    {
        endptr++;
    }

    if (*endptr != '\0' ||
        number < INT_MIN || number > INT_MAX)
    {
        printf("Error: Please enter a valid integer.\n");
        return 0;
    }

    if (number < min || number > max)
    {
        if (min == 1 && max == 24)
            printf("Error: Invalid number of months.\n");
        else
            printf("Error: Invalid plan.\n");

        return 0;
    }

    *value = (int)number;
    return 1;
}

int getMemberDetails(struct Member *m)
{
    if (!readLine("Enter member name: ", m->name, sizeof(m->name)))
    {
        return 0;
    }

    if (m->name[0] == '\0')
    {
        printf("Error: Member name cannot be empty.\n");
        return 0;
    }

    if (!readInt("Enter number of months: ", 1, 24, &m->months))
    {
        return 0;
    }

    if (!readInt("Enter plan type (1-Basic, 2-Standard, 3-Premium): ", 1, 3, &m->plan_type))
    {
        return 0;
    }

    return 1;
}

int getMonthlyFee(struct Member *m)
{
    switch (m->plan_type)
    {
    case 1:
        return BASIC_PRICE;

    case 2:
        return STANDARD_PRICE;

    case 3:
        return PREMIUM_PRICE;

    default:
        return 0;
    }
}

double calculateSubtotal(int monthlyFee, int months)
{
    return (double)monthlyFee * months;
}

double calculateDiscount(struct Member *m, double subtotal)
{
    if (m->months >= 12)
    {
        return subtotal * 0.20;
    }
    else if (m->months >= 6)
    {
        return subtotal * 0.10;
    }
    else
    {
        return 0.0;
    }
}

int displayBill(struct Member *m, double subtotal, double discount)
{
    const char *plan;

    switch (m->plan_type)
    {
    case 1:
        plan = "Basic";
        break;

    case 2:
        plan = "Standard";
        break;

    case 3:
        plan = "Premium";
        break;

    default:
        printf("Error: Invalid plan type.\n");
        return 0;
    }

    double finalAmount = subtotal - discount + JOINING_FEE;

    printf("\nMember: %s\n", m->name);
    printf("Plan: %s\n", plan);
    printf("Months: %d\n", m->months);
    printf("Subtotal: %.2f\n", subtotal);
    printf("Discount: %.2f\n", discount);
    printf("Joining Fee: %.2f\n", (double)JOINING_FEE);
    printf("Final Amount: %.2f\n", finalAmount);

    return 1;
}

int processMembership(struct Member *m)
{
    int monthlyFee = getMonthlyFee(m);

    if (monthlyFee == 0)
    {
        printf("Error: Invalid plan type.\n");
        return 0;
    }

    double subtotal =
        calculateSubtotal(monthlyFee, m->months);

    double discount =
        calculateDiscount(m, subtotal);

    return displayBill(m, subtotal, discount);
}

int main()
{
    struct Member *m = malloc(sizeof(struct Member));

    if (m == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    if (!getMemberDetails(m))
    {
        free(m);
        return 1;
    }

    if (!processMembership(m))
    {
        free(m);
        return 1;
    }

    free(m);
    m = NULL;

    return 0;
}
