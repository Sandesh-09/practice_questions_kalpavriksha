#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

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

int **createInventory(int rows, int cols)
{
    int **inventory = malloc(rows * sizeof(int *));

    if (inventory == NULL)
        return NULL;

    for (int i = 0; i < rows; i++)
    {
        inventory[i] = malloc(cols * sizeof(int));

        if (inventory[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(inventory[j]);

            free(inventory);
            return NULL;
        }
    }

    return inventory;
}

void inputInventory(int **inventory, int rows, int cols)
{
    printf("\nEnter inventory quantities:\n");

    for (int i = 0; i < rows; i++)
    {
        printf("\nZone %d:\n", i);

        for (int j = 0; j < cols; j++)
        {
            int val;

            while (!readInt("Enter stock quantity: ", 0, INT_MAX, &val))
                printf("Please enter a valid non-negative quantity.\n");

            inventory[i][j] = val;
        }
    }
}

void displayInventory(int **inventory, int rows, int cols)
{
    printf("\nWarehouse Inventory:\n\n");

    for (int i = 0; i < rows; i++)
    {
        printf("Zone %d: ", i);

        for (int j = 0; j < cols; j++)
            printf("%d ", inventory[i][j]);

        printf("\n");
    }
}

void addStock(int **inventory, int rows, int cols)
{
    int zone, bin, quantity;

    printf("\nAdd Stock\n");

    while (!readInt("Enter zone number: ", 0, rows - 1, &zone))
        printf("Invalid zone number.\n");

    while (!readInt("Enter bin number: ", 0, cols - 1, &bin))
        printf("Invalid bin number.\n");

    while (!readInt("Enter quantity to add: ", 1, INT_MAX, &quantity))
        printf("Quantity must be positive.\n");

    if (inventory[zone][bin] > INT_MAX - quantity)
    {
        printf("Error: Stock quantity overflow.\n");
        return;
    }

    inventory[zone][bin] += quantity;

    printf("Stock added successfully.\n");
}

void dispatchStock(int **inventory, int rows, int cols)
{
    int zone, bin, quantity;

    printf("\nDispatch Stock\n");

    while (!readInt("Enter zone number: ", 0, rows - 1, &zone))
        printf("Invalid zone number.\n");

    while (!readInt("Enter bin number: ", 0, cols - 1, &bin))
        printf("Invalid bin number.\n");

    while (!readInt("Enter quantity to dispatch: ", 1, INT_MAX, &quantity))
        printf("Quantity must be positive.\n");

    if (quantity > inventory[zone][bin])
    {
        printf("Error: Insufficient stock.\n");
        return;
    }

    inventory[zone][bin] -= quantity;

    printf("Stock dispatched successfully.\n");
}

void calculateInventory(int **inventory, int rows, int cols)
{
    long long grandTotal = 0;

    printf("\nInventory Summary:\n\n");

    for (int i = 0; i < rows; i++)
    {
        long long zoneTotal = 0;

        for (int j = 0; j < cols; j++)
            zoneTotal += inventory[i][j];

        printf("Total stock in Zone %d: %lld\n", i, zoneTotal);

        grandTotal += zoneTotal;
    }

    printf("\nTotal warehouse inventory: %lld\n", grandTotal);
}

void findMaximum(int **inventory, int rows, int cols)
{
    int maxStock = inventory[0][0];
    int maxZone = 0;
    int maxBin = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (inventory[i][j] > maxStock)
            {
                maxStock = inventory[i][j];
                maxZone = i;
                maxBin = j;
            }
        }
    }

    printf("\nMaximum stock: %d\n", maxStock);
    printf("Location: Zone %d, Bin %d\n", maxZone, maxBin);
}

void freeInventory(int **inventory, int rows)
{
    for (int i = 0; i < rows; i++)
        free(inventory[i]);

    free(inventory);
}

int main()
{
    int rows, cols;

    printf("Smart Warehouse Inventory Management\n");

    while (!readInt("Enter number of zones: ", 1, 100, &rows))
        printf("Please enter a valid number of zones.\n");

    while (!readInt("Enter number of bins per zone: ", 1, 100, &cols))
        printf("Please enter a valid number of bins.\n");

    int **inventory = createInventory(rows, cols);

    if (inventory == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    inputInventory(inventory, rows, cols);
    displayInventory(inventory, rows, cols);
    addStock(inventory, rows, cols);
    dispatchStock(inventory, rows, cols);
    displayInventory(inventory, rows, cols);
    calculateInventory(inventory, rows, cols);
    findMaximum(inventory, rows, cols);
    freeInventory(inventory, rows);

    inventory = NULL;
    return 0;
}
