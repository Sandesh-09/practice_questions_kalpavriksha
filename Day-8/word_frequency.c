#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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

    printf("Error: Input cannot exceed 100 characters.\n");
    return 0;
}

int countWord(char str[], char word[])
{
    int cnt = 0;
    int i = 0;
    int j;

    char temp[101];

    while (str[i] != '\0')
    {
        while (str[i] != '\0' && !isalnum((unsigned char)str[i]))
            i++;

        j = 0;

        while (str[i] != '\0' && isalnum((unsigned char)str[i]))
        {
            if (j < 100)
            {
                temp[j] = tolower((unsigned char)str[i]);
                j++;
            }

            i++;
        }

        temp[j] = '\0';

        if (j > 0 && strcmp(temp, word) == 0)
            cnt++;
    }

    return cnt;
}

void printFrequencies(char str[])
{
    char words[101][101];
    char temp[101];

    int i = 0;
    int j;
    int k;
    int cnt = 0;

    while (str[i] != '\0')
    {
        while (str[i] != '\0' && !isalnum((unsigned char)str[i]))
            i++;

        j = 0;

        while (str[i] != '\0' && isalnum((unsigned char)str[i]))
        {
            if (j < 100)
            {
                temp[j] = tolower((unsigned char)str[i]);
                j++;
            }

            i++;
        }

        temp[j] = '\0';

        if (j == 0)
            continue;

        int found = 0;

        for (k = 0; k < cnt; k++)
        {
            if (strcmp(words[k], temp) == 0)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            strcpy(words[cnt], temp);
            cnt++;
        }
    }

    if (cnt == 0)
    {
        printf("\nNo words found.\n");
        return;
    }

    printf("\nFrequencies:\n");

    int maxCnt = 0;
    int maxIndex = 0;

    for (i = 0; i < cnt; i++)
    {
        int freq = countWord(str, words[i]);

        printf("%s: %d\n", words[i], freq);

        if (freq > maxCnt)
        {
            maxCnt = freq;
            maxIndex = i;
        }
    }

    printf("\nMost frequent word: %s (%d times)\n",
           words[maxIndex], maxCnt);
}

int main()
{
    char str[101];

    if (!readLine("Input text: ", str, sizeof(str)))
        return 1;

    printFrequencies(str);

    return 0;
}
