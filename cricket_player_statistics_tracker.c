/*

2. Cricket Player Statistics Tracker

Design a console-based Cricket Player Statistics Tracker in C that analyzes batting performance across three matches.

Requirements

Use a structure to store: Jersey Number, Player Name, Runs in three matches.
Calculate Total Runs, Batting Average, and Highest Score using arithmetic operators and comparisons.
Assign a Rating using if-else or switch-case:
Average	Rating
≥ 60	Star
≥ 40	Good
≥ 20	Average
< 20	Poor
Display a Form Graph with * printed per 10 runs scored in each match, one row per match (use nested loops).
If a player’s total runs is 0, skip the graph using continue.
Use functions for total, average, highest, and rating.
Use recursion to find the maximum total runs among all players.
Demonstrate variable scope with a global variable tracking the best player’s jersey number and a local variable inside loops.

Constraints: 1 ≤ N ≤ 20, 0 ≤ Runs ≤ 200.

Input Format

N
Jersey Name Run1 Run2 Run3

Sample Input

2
18 Virat 85 42 30
7 Dhoni 0 0 0

Sample Output

Jersey: 18
Name: Virat
Total: 157
Average: 52.33
Highest: 85
Rating: Good
Match 1: ********
Match 2: ****
Match 3: ***
Jersey: 7
Name: Dhoni
Total: 0
Average: 0.00
Highest: 0
Rating: Poor
Maximum Total (via recursion): 157
Best Player Jersey: 18

*/

// code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define MAX_PLAYERS 20
#define MATCHES 3

int bestPlayerJersey = 0;

struct Player
{
    int jerseyNumber;
    char name[50];
    int runs[MATCHES];
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

int getPlayerDetails(struct Player *p)
{
    if (!readInt("Enter Jersey Number: ",
                 1, INT_MAX, &p->jerseyNumber))
        return 0;

    if (!readLine("Enter Player Name: ",
                  p->name, sizeof(p->name)))
        return 0;

    if (p->name[0] == '\0')
    {
        printf("Error: Player name cannot be empty.\n");
        return 0;
    }

    for (int i = 0; i < MATCHES; i++)
    {
        printf("Match %d\n", i + 1);

        if (!readInt("Enter Runs: ", 0, 200, &p->runs[i]))
            return 0;
    }

    return 1;
}

int calculateTotal(struct Player *p)
{
    int total = 0;

    for (int i = 0; i < MATCHES; i++)
        total += p->runs[i];

    return total;
}

float calculateAverage(int total)
{
    return (float)total / MATCHES;
}

int calculateHighest(struct Player *p)
{
    int highest = p->runs[0];

    for (int i = 1; i < MATCHES; i++)
    {
        if (p->runs[i] > highest)
            highest = p->runs[i];
    }

    return highest;
}

char *calculateRating(float average)
{
    if (average >= 60)
        return "Star";
    else if (average >= 40)
        return "Good";
    else if (average >= 20)
        return "Average";
    else
        return "Poor";
}

void displayFormGraph(struct Player *p)
{
    for (int i = 0; i < MATCHES; i++)
    {
        printf("Match %d: ", i + 1);

        int stars = p->runs[i] / 10;

        for (int j = 0; j < stars; j++)
            printf("*");

        printf("\n");
    }
}

void displayPlayer(struct Player *p, int total,
                   float average, int highest)
{
    printf("Jersey: %d\n", p->jerseyNumber);
    printf("Name: %s\n", p->name);
    printf("Total: %d\n", total);
    printf("Average: %.2f\n", average);
    printf("Highest: %d\n", highest);
    printf("Rating: %s\n", calculateRating(average));
}

void processPlayers(struct Player *players, int n)
{
    int maxRuns = -1;

    for (int i = 0; i < n; i++)
    {
        int total = calculateTotal(players + i);
        float average = calculateAverage(total);
        int highest = calculateHighest(players + i);

        displayPlayer(players + i, total, average, highest);

        if (total > maxRuns)
        {
            maxRuns = total;
            bestPlayerJersey = (players + i)->jerseyNumber;
        }

        if (total == 0)
        {
            printf("\n");
            continue;
        }

        displayFormGraph(players + i);
        printf("\n");
    }
}

int findMaximumTotal(int total[], int n)
{
    if (n == 1)
        return total[0];

    int maximum = findMaximumTotal(total, n - 1);

    if (total[n - 1] > maximum)
        return total[n - 1];

    return maximum;
}

int main()
{
    int n;

    if (!readInt("Enter number of players: ",
                 1, MAX_PLAYERS, &n))
        return 1;

    struct Player *players = malloc(n * sizeof(struct Player));
    int *totalRuns = malloc(n * sizeof(int));

    if (players == NULL || totalRuns == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        free(players);
        free(totalRuns);
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter details of Player %d:\n", i + 1);

        if (!getPlayerDetails(players + i))
        {
            free(players);
            free(totalRuns);
            return 1;
        }
    }

    for (int i = 0; i < n; i++)
        totalRuns[i] = calculateTotal(players + i);

    printf("\nPlayer Statistics\n\n");

    processPlayers(players, n);

    printf("Maximum Total: %d\n",
           findMaximumTotal(totalRuns, n));

    printf("Best Player Jersey: %d\n", bestPlayerJersey);

    free(players);
    free(totalRuns);

    players = NULL;
    totalRuns = NULL;

    return 0;
}
