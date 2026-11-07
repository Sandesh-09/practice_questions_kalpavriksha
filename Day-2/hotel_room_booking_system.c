/* 3. Hotel Room Booking System

Design a console-based program in C for a hotel reception desk. The program should accept guest details, calculate the stay cost, apply a long-stay discount, and add tax.

Requirements

Read the guest name, num of nights, and room type from the user.
Support three room types: Standard, Deluxe, and Suite. The user enters 1, 2, or 3.
Declare the prices per night and the tax rate as constants: Standard = 2000, Deluxe = 3500, Suite = 6000, and GST = 12%.
Use switch-case to select the price per night.
Calculate Subtotal = nights × price.
Use if-else to apply a 15% discount when the guest stays 7 or more nights. Otherwise the discount is 0.
Calculate GST on the discounted amount (Subtotal − Discount).
Calculate Final Bill = (Subtotal − Discount) + GST.
Store the booking in a structure allocated with malloc, access it using a pointer, and release it with free.
Display an error message if the room type or num of nights is invalid.
Choice	Room Type	Price per Night
1	Standard	2000
2	Deluxe	3500
3	Suite	6000

Constraints: 1 ≤ Nights ≤ 30, room type must be 1, 2, or 3.

Input Format

Guest name (single word)
num of nights
Room type (1, 2, or 3)

Output Format

Guest: <name>
Room Type: <type>
Nights: <nights>
Subtotal: <amount>
Discount: <amount>
GST: <amount>
Final Bill: <amount>

Sample Test Case 1

Input:
Rohan 7 2

Output:
Guest: Rohan
Room Type: Deluxe
Nights: 7
Subtotal: 24500.00
Discount: 3675.00
GST: 2499.00
Final Bill: 23324.00

Sample Test Case 2

Input:
Neha 2 1

Output:
Guest: Neha
Room Type: Standard
Nights: 2
Subtotal: 4000.00
Discount: 0.00
GST: 480.00
Final Bill: 4480.00

Sample Test Case 3 (invalid input)

Input:
Tina 3 5

Output:
Error: Invalid room type.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define STANDARD_PRICE 2000
#define DELUXE_PRICE 3500
#define SUITE_PRICE 6000
#define GST_RATE 0.12

struct Booking
{
    char name[100];
    int nights;
    int room_type;
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
        if (min == 1 && max == 30)
            printf("Error: Invalid num of nights.\n");
        else
            printf("Error: Invalid room type.\n");

        return 0;
    }

    *value = (int)num;
    return 1;
}

int getBookingDetails(struct Booking *b)
{
    if (!readLine("Enter guest name: ",
                  b->name, sizeof(b->name)))
    {
        return 0;
    }

    if (b->name[0] == '\0')
    {
        printf("Error: Guest name cannot be empty.\n");
        return 0;
    }

    if (!readInt("Enter num of nights: ",
                 1, 30, &b->nights))
    {
        return 0;
    }

    if (!readInt("Enter room type (1-Standard, 2-Deluxe, 3-Suite): ",
                 1, 3, &b->room_type))
    {
        return 0;
    }

    return 1;
}

int getRoomPrice(struct Booking *b)
{
    switch (b->room_type)
    {
    case 1:
        return STANDARD_PRICE;

    case 2:
        return DELUXE_PRICE;

    case 3:
        return SUITE_PRICE;

    default:
        return 0;
    }
}

double calculateSubtotal(int price, int nights)
{
    return (double)price * nights;
}

double calculateDiscount(struct Booking *b, double subtotal)
{
    if (b->nights >= 7)
    {
        return subtotal * 0.15;
    }

    return 0.0;
}

double calculateGST(double discountedAmount)
{
    return discountedAmount * GST_RATE;
}

int displayBill(struct Booking *b, double subtotal,
                double discount, double gst)
{
    const char *room;

    switch (b->room_type)
    {
    case 1:
        room = "Standard";
        break;

    case 2:
        room = "Deluxe";
        break;

    case 3:
        room = "Suite";
        break;

    default:
        printf("Error: Invalid room type.\n");
        return 0;
    }

    double finalBill = (subtotal - discount) + gst;

    printf("\nGuest: %s\n", b->name);
    printf("Room Type: %s\n", room);
    printf("Nights: %d\n", b->nights);
    printf("Subtotal: %.2f\n", subtotal);
    printf("Discount: %.2f\n", discount);
    printf("GST: %.2f\n", gst);
    printf("Final Bill: %.2f\n", finalBill);

    return 1;
}

int processBooking(struct Booking *b)
{
    int price = getRoomPrice(b);

    if (price == 0)
    {
        printf("Error: Invalid room type.\n");
        return 0;
    }

    double subtotal =
        calculateSubtotal(price, b->nights);

    double discount =
        calculateDiscount(b, subtotal);

    double discountedAmount = subtotal - discount;

    double gst = calculateGST(discountedAmount);

    return displayBill(b, subtotal, discount, gst);
}

int main()
{
    struct Booking *b = malloc(sizeof(struct Booking));

    if (b == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    if (!getBookingDetails(b))
    {
        free(b);
        return 1;
    }

    if (!processBooking(b))
    {
        free(b);
        return 1;
    }

    free(b);
    b = NULL;

    return 0;
}
