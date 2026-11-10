/*
Range Sum Queries

Problem Statement
You are given an array of integers and several queries. Each query gives two indices l and r (1-indexed, inclusive). For every query, print the sum of the elements from position l to position r.
Requirements
•	Build a prefix sum array once, in O(n).
•	Answer every query in O(1) using the prefix sums.
•	Use a 64-bit integer type for the sums.
Input Format
The first line contains two integers n and q.
The second line contains n space-separated integers.
Each of the next q lines contains two integers l and r.
Constraints
•	1 <= n, q <= 10^5
•	-10^9 <= array[i] <= 10^9
•	1 <= l <= r <= n
Output Format
For each query, print the range sum on its own line.
Sample Input 0
5 3
1 2 3 4 5
1 3
2 5
4 4

Sample Output 0
6
14
4

Sample Input 1
3 2
-5 10 -5
1 3
2 2

Sample Output 1
0
10

Edge Cases to Handle
•	Query with l = 1 (prefix[l-1] is the empty prefix).
•	Query with l = r.
•	Negative values.
•	Sums that overflow a 32-bit integer.
Concepts Tested
Prefix sum construction, 1-indexed versus 0-indexed handling, O(1) range queries, integer overflow.

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int readInt(const char *message, int min, int max, int *value)
{
    char input[100];
    char *endptr;
    long number;

    printf("%s", message);

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        printf("Error: Unable to read input.\n");
        return 0;
    }

    errno = 0;
    number = strtol(input, &endptr, 10);

    if (input == endptr || errno == ERANGE)
    {
        printf("Error: Invalid integer input.\n");
        return 0;
    }

    while (*endptr == ' ' || *endptr == '\t' ||
           *endptr == '\n' || *endptr == '\r')
    {
        endptr++;
    }

    if (*endptr != '\0' ||
        number < INT_MIN || number > INT_MAX)
    {
        printf("Error: Invalid integer input.\n");
        return 0;
    }

    if (number < min || number > max)
    {
        printf("Error: Value out of range.\n");
        return 0;
    }

    *value = (int)number;
    return 1;
}

int buildPrefixSum(long long *arr, long long *prefix, int n)
{
    int i;

    *prefix = 0;

    for (i = 1; i <= n; i++)
    {
        *(prefix + i) = *(prefix + i - 1) + *(arr + i - 1);
    }

    return 1;
}

long long rangeSum(long long *prefix, int l, int r)
{
    return *(prefix + r) - *(prefix + l - 1);
}

int main()
{
    int n, q, l, r, i;

    if (scanf("%d %d", &n, &q) != 2)
    {
        printf("Error: Invalid input.\n");
        return 1;
    }

    if (n < 1 || n > 100000 || q < 1 || q > 100000)
    {
        printf("Error: Invalid n or q.\n");
        return 1;
    }

    long long *arr = malloc(n * sizeof(long long));

    if (arr == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    long long *prefix = malloc((n + 1) * sizeof(long long));

    if (prefix == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        free(arr);
        return 1;
    }

    for (i = 0; i < n; i++)
    {
        if (scanf("%lld", arr + i) != 1)
        {
            printf("Error: Invalid array input.\n");
            free(arr);
            free(prefix);
            return 1;
        }
    }

    buildPrefixSum(arr, prefix, n);

    for (i = 0; i < q; i++)
    {
        if (scanf("%d %d", &l, &r) != 2)
        {
            printf("Error: Invalid query input.\n");
            free(arr);
            free(prefix);
            return 1;
        }

        if (l < 1 || r > n || l > r)
        {
            printf("Error: Invalid query range.\n");
            free(arr);
            free(prefix);
            return 1;
        }

        printf("%lld\n", rangeSum(prefix, l, r));
    }

    free(arr);
    free(prefix);

    arr = NULL;
    prefix = NULL;

    return 0;
}
