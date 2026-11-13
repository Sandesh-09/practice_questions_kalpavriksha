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

    printf("Error: Input is too long. Maximum 100 characters allowed.\n");
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

void removeVowels(char str[])
{
    int i = 0, j = 0;

    while (str[i] != '\0')
    {
        char ch = str[i];

        if (ch != 'a' && ch != 'e' && ch != 'i' &&
            ch != 'o' && ch != 'u' && ch != 'A' &&
            ch != 'E' && ch != 'I' && ch != 'O' &&
            ch != 'U')
        {
            str[j] = str[i];
            j++;
        }

        i++;
    }

    str[j] = '\0';
}

void reverseEachWord(char str[])
{
    int i = 0;

    while (str[i] != '\0')
    {
        if (isspace((unsigned char)str[i]))
        {
            i++;
            continue;
        }

        int start = i;

        while (str[i] != '\0' && !isspace((unsigned char)str[i]))
            i++;

        int end = i - 1;

        while (start < end)
        {
            char temp = str[start];
            str[start] = str[end];
            str[end] = temp;

            start++;
            end--;
        }
    }
}

int main()
{
    char original[101] = "";
    char copy[101];
    int choice;
    int textEntered = 0;

    while (1)
    {
        printf("\n----- MENU -----\n");
        printf("1. Enter Text\n");
        printf("2. Remove Vowels\n");
        printf("3. Reverse Each Word\n");
        printf("4. Exit\n");

        if (!readInt("Enter your choice: ", 1, 4, &choice))
            continue;

        switch (choice)
        {
        case 1:
            if (readLine("Input text: ", original, sizeof(original)))
            {
                textEntered = 1;
                printf("Text saved successfully.\n");
            }
            break;

        case 2:
            if (!textEntered)
            {
                printf("Error: Please enter text first.\n");
                break;
            }

            strcpy(copy, original);
            removeVowels(copy);

            printf("\nOriginal Text: %s\n", original);
            printf("Remove Vowels: %s\n", copy);
            break;

        case 3:
            if (!textEntered)
            {
                printf("Error: Please enter text first.\n");
                break;
            }

            strcpy(copy, original);
            reverseEachWord(copy);

            printf("\nOriginal Text: %s\n", original);
            printf("Reverse Each Word: %s\n", copy);
            break;

        case 4:
            printf("Exiting program.\n");
            return 0;

        default:
            printf("Error: Invalid menu choice.\n");
        }
    }
}
