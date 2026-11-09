/*

5. Restaurant Order Billing System

Design a console-based program in C for a restaurant billing counter. The program should accept customer and order details, calculate the bill, apply a discount for bulk orders, and add a service charge.

Requirements

Read the customer name, num of plates, and meal type from the user.
Support three meal types: Veg Thali, Non-Veg Thali, and Special Thali. The user enters 1, 2, or 3.
Declare the prices and the service charge rate as constants: Veg = 120, Non-Veg = 180, Special = 300, and Service Charge = 5%.
Use switch-case to select the price per plate.
Calculate Subtotal = plates × price.
Use if-else to apply a 10% discount when the customer orders 4 or more plates. Otherwise the discount is 0.
Calculate the Service Charge on the discounted amount (Subtotal − Discount).
Calculate Final Bill = (Subtotal − Discount) + Service Charge.
Store the order in a structure allocated with malloc, access it using a pointer (->), and release it with free.
Display an error message if the meal type or num of plates is invalid.
Choice	Meal Type	Price per Plate
1	Veg Thali	120
2	Non-Veg Thali	180
3	Special Thali	300

Constraints: 1 ≤ Plates ≤ 20, meal type must be 1, 2, or 3.

Input Format

Customer name (single word)
num of plates
Meal type (1, 2, or 3)

Output Format

Customer: <name>
Meal Type: <type>
Plates: <plates>
Subtotal: <amount>
Discount: <amount>
Service Charge: <amount>
Final Bill: <amount>

Sample Test Case 1

Input:
Isha 4 3

Output:
Customer: Isha
Meal Type: Special Thali
Plates: 4
Subtotal: 1200.00
Discount: 120.00
Service Charge: 54.00
Final Bill: 1134.00

Sample Test Case 2

Input:
Arjun 2 1

Output:
Customer: Arjun
Meal Type: Veg Thali
Plates: 2
Subtotal: 240.00
Discount: 0.00
Service Charge: 12.00
Final Bill: 252.00

Sample Test Case 3 (invalid input)

Input:
Dev 25 2

Output:
Error: Invalid num of plates.

Sample Test Case 4 (invalid input)

Input:
Riya 3 4

Output:
Error: Invalid meal type.

*/

// solution code

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define VEG_PRICE 120
#define NON_VEG_PRICE 180
#define SPECIAL_PRICE 300
#define SERVICE_CHARGE_RATE 0.05

struct Order
{
    char name[100];
    int plates;
    int meal_type;
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
        if (min == 1 && max == 20)
            printf("Error: Invalid num of plates.\n");
        else
            printf("Error: Invalid meal type.\n");

        return 0;
    }

    *value = (int)num;
    return 1;
}

int getOrderDetails(struct Order *o)
{
    if (!readLine("Enter customer name: ",
                  o->name, sizeof(o->name)))
    {
        return 0;
    }

    if (o->name[0] == '\0')
    {
        printf("Error: Customer name cannot be empty.\n");
        return 0;
    }

    if (!readInt("Enter num of plates: ",
                 1, 20, &o->plates))
    {
        return 0;
    }

    if (!readInt("Enter meal type (1-Veg, 2-Non-Veg, 3-Special): ",
                 1, 3, &o->meal_type))
    {
        return 0;
    }

    return 1;
}

int getMealPrice(struct Order *o)
{
    switch (o->meal_type)
    {
    case 1:
        return VEG_PRICE;

    case 2:
        return NON_VEG_PRICE;

    case 3:
        return SPECIAL_PRICE;

    default:
        return 0;
    }
}

double calculateSubtotal(int price, int plates)
{
    return (double)price * plates;
}

double calculateDiscount(struct Order *o, double subtotal)
{
    if (o->plates >= 4)
    {
        return subtotal * 0.10;
    }

    else
    {
        return 0.0;
    }
}

double calculateServiceCharge(double discountedAmount)
{
    return discountedAmount * SERVICE_CHARGE_RATE;
}

int displayBill(struct Order *o, double subtotal,
                double discount, double serviceCharge)
{
    const char *meal;

    switch (o->meal_type)
    {
    case 1:
        meal = "Veg Thali";
        break;

    case 2:
        meal = "Non-Veg Thali";
        break;

    case 3:
        meal = "Special Thali";
        break;

    default:
        printf("Error: Invalid meal type.\n");
        return 0;
    }

    double finalBill =
        (subtotal - discount) + serviceCharge;

    printf("\nCustomer: %s\n", o->name);
    printf("Meal Type: %s\n", meal);
    printf("Plates: %d\n", o->plates);
    printf("Subtotal: %.2f\n", subtotal);
    printf("Discount: %.2f\n", discount);
    printf("Service Charge: %.2f\n", serviceCharge);
    printf("Final Bill: %.2f\n", finalBill);

    return 1;
}

int processOrder(struct Order *o)
{
    int price = getMealPrice(o);

    if (price == 0)
    {
        printf("Error: Invalid meal type.\n");
        return 0;
    }

    double subtotal =
        calculateSubtotal(price, o->plates);

    double discount =
        calculateDiscount(o, subtotal);

    double discountedAmount = subtotal - discount;

    double serviceCharge =
        calculateServiceCharge(discountedAmount);

    return displayBill(o, subtotal, discount, serviceCharge);
}

int main()
{
    struct Order *o = malloc(sizeof(struct Order));

    if (o == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    if (!getOrderDetails(o))
    {
        free(o);
        return 1;
    }

    if (!processOrder(o))
    {
        free(o);
        return 1;
    }

    free(o);
    o = NULL;

    return 0;
}
