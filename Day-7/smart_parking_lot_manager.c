/*

Smart Parking Lot Fee Analyzer

Design a console-based Smart Parking Lot Fee Analyzer program in C that accepts vehicle details as input and evaluates the parking fee based on the time spent in three zones of a parking lot.

The program should calculate total hours, average hours per zone, assign a fee category, and display a usage pattern using # symbols based on the category. It should also demonstrate programming concepts like arithmetic operators, control flow, loops, functions, recursion, structures, and variable scope.

Requirements

Use a structure to store vehicle details: Vehicle Number, Owner Name, Hours spent in three zones (Zone A, Zone B, Zone C).
Calculate Total Hours and Average Hours using arithmetic operators.
Assign a Fee Category using if-else or switch-case logic:
Average Hours	Category
≥ 8	X (Extended)
≥ 6	H (Heavy)
≥ 4	M (Medium)
≥ 2	L (Light)
< 2	S (Short)
Calculate the Fee using total hours: ₹20 per hour for Category X, ₹15 for H, ₹12 for M, ₹10 for L, and ₹5 for S. Use switch-case for this.
Display a Usage Pattern of # symbols based on the category (X: 5, H: 4, M: 3, L: 2).
If a vehicle’s average hours is below 2, skip printing the pattern using the continue statement.
Include loops to iterate over multiple vehicles, functions to compute total, average, category, and fee, recursion to compute the total fee collected across all vehicles, and demonstrate variable scope (a global variable counting vehicles processed, and a local variable inside the loop).
Use proper input/output formatting to clearly show results for each vehicle.

Constraints

Number of vehicles: 1 ≤ N ≤ 100
Hours in each zone: 0 ≤ Hours ≤ 24

Input Format

First line: An integer N (number of vehicles)
Next N lines: Vehicle_Number Owner_Name Hours1 Hours2 Hours3

Output Format
For each vehicle, print:

Vehicle: <vehicle_number>
Owner: <owner_name>
Total Hours: <total_hours>
Average Hours: <average_hours>
Category: <category>
Fee: <fee>
Usage: <pattern of # based on category>

At the end, print:

Total Fee Collected (via recursion): <total_fee>
Vehicles Processed: <count>

Test Case

Input:

3
1001 Rahul 8 7 9
1002 Sneha 3 2 4
1003 Amit 1 0 1

Output:

Vehicle: 1001
Owner: Rahul
Total Hours: 24
Average Hours: 8.00
Category: X
Fee: 480
Usage: #####
Vehicle: 1002
Owner: Sneha
Total Hours: 9
Average Hours: 3.00
Category: L
Fee: 90
Usage: ##
Vehicle: 1003
Owner: Amit
Total Hours: 2
Average Hours: 0.67
Category: S
Fee: 10
Total Fee Collected (via recursion): 580
Vehicles Processed: 3

*/

#include <stdio.h>
#include <stdlib.h>

int cnt = 0;

struct Vehicle
{
    int num;
    char name[50];
    int a, b, c;
    int total;
    float avg;
    char category;
    int fee;
};

int calculateTotal(struct Vehicle *v)
{
    return v->a + v->b + v->c;
}

float calculateAverage(struct Vehicle *v)
{
    return (float)v->total / 3;
}

char calculateCategory(float avg)
{
    if (avg >= 8)
        return 'X';
    else if (avg >= 6)
        return 'H';
    else if (avg >= 4)
        return 'M';
    else if (avg >= 2)
        return 'L';
    else
        return 'S';
}

int calculateFee(struct Vehicle *v)
{
    int rate;

    switch (v->category)
    {
    case 'X':
        rate = 20;
        break;

    case 'H':
        rate = 15;
        break;

    case 'M':
        rate = 12;
        break;

    case 'L':
        rate = 10;
        break;

    case 'S':
        rate = 5;
        break;

    default:
        rate = 0;
    }

    return v->total * rate;
}

void displayPattern(char category)
{
    int n = 0;

    switch (category)
    {
    case 'X':
        n = 5;
        break;

    case 'H':
        n = 4;
        break;

    case 'M':
        n = 3;
        break;

    case 'L':
        n = 2;
        break;
    }

    for (int i = 0; i < n; i++)
    {
        printf("#");
    }

    printf("\n");
}

int calculateTotalFee(struct Vehicle *v, int n)
{
    if (n == 0)
        return 0;

    return v[n - 1].fee + calculateTotalFee(v, n - 1);
}

int main()
{
    int n;

    scanf("%d", &n);

    struct Vehicle *v = (struct Vehicle *)malloc(n * sizeof(struct Vehicle));

    if (v == NULL)
    {
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        int local = i + 1;

        scanf("%d %49s %d %d %d",
              &v[i].num, v[i].name,
              &v[i].a, &v[i].b, &v[i].c);

        v[i].total = calculateTotal(&v[i]);
        v[i].avg = calculateAverage(&v[i]);
        v[i].category = calculateCategory(v[i].avg);
        v[i].fee = calculateFee(&v[i]);

        cnt++;

        printf("Vehicle: %d\n", v[i].num);
        printf("Owner: %s\n", v[i].name);
        printf("Total Hours: %d\n", v[i].total);
        printf("Average Hours: %.2f\n", v[i].avg);
        printf("Category: %c\n", v[i].category);
        printf("Fee: %d\n", v[i].fee);

        if (v[i].avg < 2)
        {
            continue;
        }

        printf("Usage: ");
        displayPattern(v[i].category);
    }

    int totalFee = calculateTotalFee(v, n);

    printf("Total Fee Collected (via recursion): %d\n", totalFee);
    printf("Vehicles Processed: %d\n", cnt);

    free(v);

    return 0;
}
