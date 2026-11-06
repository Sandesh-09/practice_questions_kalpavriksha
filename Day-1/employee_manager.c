/*
1. Employee Salary Calculator

Design a console-based Employee Salary Calculator in C that accepts employee details and computes their salary components and a performance rating.

Requirements

Use a structure to store: Employee ID, Name, Basic Salary, Years of Experience.
Calculate HRA (20% of basic), DA (10% of basic), and Gross Salary using arithmetic operators.
Calculate Tax using if-else or switch-case:
Gross Salary	Tax Rate
> 80000	20%
> 50000	10%
> 30000	5%
≤ 30000	0%
Compute Net Salary = Gross − Tax.
Assign a Category based on experience: Senior (≥ 10 yrs), Mid (≥ 5), Junior (≥ 2), Trainee (< 2).
Print a bar of # symbols equal to (Net Salary / 10000), rounded down, using a loop.
If Net Salary is below 20000, skip the bar using continue.
Use functions for gross, tax, and category calculation.
Use recursion to compute the sum of all net salaries.
Demonstrate variable scope using a global counter for total employees processed.

Constraints: 1 ≤ N ≤ 50, Basic Salary ≤ 200000, Experience ≤ 40.

Input Format

N
ID Name Basic Experience

Sample Input

2
101 Rahul 40000 6
102 Sneha 15000 1

Sample Output

ID: 101
Name: Rahul
Gross: 52000.00
Tax: 5200.00
Net: 46800.00
Category: Mid
Bar: ####
ID: 102
Name: Sneha
Gross: 19500.00
Tax: 0.00
Net: 19500.00
Category: Trainee
Total Net Salary (via recursion): 66300.00
Employees Processed: 2

*/

// solution code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>

#define MAX_EMPLOYEES 50

int totalEmployees = 0;

struct Employee
{
    int id;
    char name[50];
    float basicSalary;
    int experience;
};

int readLine(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) == NULL)
        return 0;

    int len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    else if (!feof(stdin))
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        return -1;
    }

    return 1;
}

int readInt(int min, int max, int *value)
{
    char line[100];
    char *end;
    long num;

    while (1)
    {
        if (!readLine(line, sizeof(line)))
            return 0;

        errno = 0;
        num = strtol(line, &end, 10);

        while (isspace((unsigned char)*end))
            end++;

        if (line != end && *end == '\0' &&
            errno != ERANGE && num >= min && num <= max)
        {
            *value = (int)num;
            return 1;
        }

        printf("Invalid input. Enter again: ");
    }
}

int getEmployeeDetails(struct Employee *emp)
{
    char line[100];
    char *end;
    float salary;

    if (!readInt(1, INT_MAX, &emp->id))
        return 0;

    if (!readLine(emp->name, sizeof(emp->name)))
        return 0;

    if (emp->name[0] == '\0')
    {
        printf("Error: Employee name cannot be empty.\n");
        return 0;
    }

    if (!readLine(line, sizeof(line)))
        return 0;

    errno = 0;
    salary = strtof(line, &end);

    while (isspace((unsigned char)*end))
        end++;

    if (line == end || *end != '\0' ||
        errno == ERANGE || !isfinite(salary) ||
        salary < 0 || salary > 200000)
    {
        printf("Error: Invalid basic salary.\n");
        return 0;
    }

    emp->basicSalary = salary;

    if (!readInt(0, 40, &emp->experience))
        return 0;

    return 1;
}

float calculateGross(float basic)
{
    float hra = basic * 0.20f;
    float da = basic * 0.10f;

    return basic + hra + da;
}

float calculateTax(float gross)
{
    if (gross > 80000)
        return gross * 0.20f;
    else if (gross > 50000)
        return gross * 0.10f;
    else if (gross > 30000)
        return gross * 0.05f;
    else
        return 0;
}

char *calculateCategory(int experience)
{
    if (experience >= 10)
        return "Senior";
    else if (experience >= 5)
        return "Mid";
    else if (experience >= 2)
        return "Junior";
    else
        return "Trainee";
}

void displaySalaryBar(float net)
{
    int count = (int)(net / 10000);

    for (int i = 0; i < count; i++)
        printf("#");

    printf("\n");
}

void displayEmployee(struct Employee *emp, float gross,
                     float tax, float net)
{
    printf("ID: %d\n", emp->id);
    printf("Name: %s\n", emp->name);
    printf("Gross: %.2f\n", gross);
    printf("Tax: %.2f\n", tax);
    printf("Net: %.2f\n", net);
    printf("Category: %s\n", calculateCategory(emp->experience));
}

void processEmployees(struct Employee *emp, float net[], int n)
{
    for (int i = 0; i < n; i++)
    {
        float gross = calculateGross((emp + i)->basicSalary);
        float tax = calculateTax(gross);

        net[i] = gross - tax;

        displayEmployee(emp + i, gross, tax, net[i]);

        totalEmployees++;

        if (net[i] < 20000)
        {
            continue;
        }

        printf("Bar: ");
        displaySalaryBar(net[i]);
    }
}

float calculateTotal(float net[], int n)
{
    if (n == 0)
        return 0;

    return net[n - 1] + calculateTotal(net, n - 1);
}

int main()
{
    struct Employee emp[MAX_EMPLOYEES];
    float net[MAX_EMPLOYEES];
    int n;

    if (!readInt(1, MAX_EMPLOYEES, &n))
        return 1;

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter details of Employee %d:\n", i + 1);

        if (!getEmployeeDetails(&emp[i]))
            return 1;
    }

    printf("\nEmployee Salary Report\n\n");

    processEmployees(emp, net, n);

    printf("Total Net Salary: %.2f\n",
           calculateTotal(net, n));

    printf("Employees Processed: %d\n", totalEmployees);

    return 0;
}
