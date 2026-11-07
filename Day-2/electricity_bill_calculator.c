/*

2. Electricity Bill Calculator

Design a console-based program in C for an electricity billing counter. The program should accept consumer details, calculate the bill, and apply a surcharge for heavy usage.

Requirements

Read the consumer name, units consumed, and connection type from the user.
Support three connection types: Domestic, Commercial, and Industrial. The user enters 1, 2, or 3.
Declare the rates and the fixed charge as constants: Domestic = 6, Commercial = 9, Industrial = 12 per unit, and Fixed Charge = 100.
Use switch-case to select the rate per unit.
Calculate Energy Charge = units × rate.
Use if-else to apply a 10% surcharge on the energy charge when units consumed are more than 300. Otherwise the surcharge is 0.
Calculate Total Bill = Energy Charge + Fixed Charge + Surcharge.
Store the details in a structure allocated with malloc, access it using a pointer (->), and release it with free.
Display an error message if the units or connection type are invalid.
Choice	Connection Type	Rate per Unit
1	Domestic	6
2	Commercial	9
3	Industrial	12

Constraints: 1 ≤ Units ≤ 1000, connection type must be 1, 2, or 3.

Input Format

Consumer name (single word)
Units consumed
Connection type (1, 2, or 3)

Output Format

Consumer: <name>
Connection: <type>
Units: <units>
Energy Charge: <amount>
Fixed Charge: <amount>
Surcharge: <amount>
Total Bill: <amount>

Sample Test Case 1

Input:
Meena 350 2

Output:
Consumer: Meena
Connection: Commercial
Units: 350
Energy Charge: 3150.00
Fixed Charge: 100.00
Surcharge: 315.00
Total Bill: 3565.00

Sample Test Case 2

Input:
Kiran 120 1

Output:
Consumer: Kiran
Connection: Domestic
Units: 120
Energy Charge: 720.00
Fixed Charge: 100.00
Surcharge: 0.00
Total Bill: 820.00

Sample Test Case 3 (invalid input)

Input:
Sam 0 2

Output:
Error: Invalid units.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define DOMESTIC_PRICE 6
#define COMMERCIAL_PRICE 9
#define INDUSTRIAL_PRICE 12
#define FIXED_CHARGE 100

struct Consumer
{
    char name[100];
    int units_consumed;
    int connection_type;
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
    long num;

    if (!readLine(message, input, sizeof(input)))
        return 0;

    errno = 0;
    num = strtol(input, &endptr, 10);

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
        num < INT_MIN || num > INT_MAX)
    {
        printf("Error: Please enter a valid integer.\n");
        return 0;
    }

    if (num < min || num > max)
    {
        if (min == 1 && max == 1000)
            printf("Error: Invalid units.\n");
        else
            printf("Error: Invalid connection type.\n");

        return 0;
    }

    *value = (int)num;
    return 1;
}

int getConsumerDetails(struct Consumer *c)
{
    if (!readLine("Enter consumer name: ",
                  c->name, sizeof(c->name)))
    {
        return 0;
    }

    if (c->name[0] == '\0')
    {
        printf("Error: Consumer name cannot be empty.\n");
        return 0;
    }

    if (!readInt("Enter units consumed: ",
                 1, 1000, &c->units_consumed))
    {
        return 0;
    }

    if (!readInt("Enter connection type (1-Domestic, 2-Commercial, 3-Industrial): ",
                 1, 3, &c->connection_type))
    {
        return 0;
    }

    return 1;
}

int getConnectionRate(struct Consumer *c)
{
    switch (c->connection_type)
    {
    case 1:
        return DOMESTIC_PRICE;

    case 2:
        return COMMERCIAL_PRICE;

    case 3:
        return INDUSTRIAL_PRICE;

    default:
        return 0;
    }
}

double calculateEnergyCharge(int rate, int units)
{
    return (double)rate * units;
}

double calculateSurcharge(struct Consumer *c, double energyCharge)
{
    if (c->units_consumed > 300)
    {
        return energyCharge * 0.10;
    }

    return 0.0;
}

int displayBill(struct Consumer *c, double energyCharge,
                double surcharge)
{
    const char *connection;

    switch (c->connection_type)
    {
    case 1:
        connection = "Domestic";
        break;

    case 2:
        connection = "Commercial";
        break;

    case 3:
        connection = "Industrial";
        break;

    default:
        printf("Error: Invalid connection type.\n");
        return 0;
    }

    printf("\nConsumer: %s\n", c->name);
    printf("Connection: %s\n", connection);
    printf("Units: %d\n", c->units_consumed);
    printf("Energy Charge: %.2f\n", energyCharge);
    printf("Fixed Charge: %.2f\n", (double)FIXED_CHARGE);
    printf("Surcharge: %.2f\n", surcharge);
    printf("Total Bill: %.2f\n",
           energyCharge + FIXED_CHARGE + surcharge);

    return 1;
}

int processBill(struct Consumer *c)
{
    int rate = getConnectionRate(c);

    if (rate == 0)
    {
        printf("Error: Invalid connection type.\n");
        return 0;
    }

    double energyCharge =
        calculateEnergyCharge(rate, c->units_consumed);

    double surcharge =
        calculateSurcharge(c, energyCharge);

    return displayBill(c, energyCharge, surcharge);
}

int main()
{
    struct Consumer *c = malloc(sizeof(struct Consumer));

    if (c == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    if (!getConsumerDetails(c))
    {
        free(c);
        return 1;
    }

    if (!processBill(c))
    {
        free(c);
        return 1;
    }

    free(c);
    c = NULL;

    return 0;
}
