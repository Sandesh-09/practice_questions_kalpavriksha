char *minRemoveToMakeValid(char *s)
{
    int n = strlen(s);

    char *temp = malloc(n + 1);
    char *ans = malloc(n + 1);

    int j = 0;
    int open = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
        {
            open++;
        }
        else if (s[i] == ')')
        {
            if (open == 0)
                continue;

            open--;
        }

        temp[j++] = s[i];
    }

    temp[j] = '\0';
    int close = 0;
    int k = 0;

    for (int i = j - 1; i >= 0; i--)
    {
        if (temp[i] == ')')
        {
            close++;
        }
        else if (temp[i] == '(')
        {
            if (close == 0)
                continue;

            close--;
        }

        ans[k++] = temp[i];
    }

    ans[k] = '\0';

    for (int i = 0; i < k / 2; i++)
    {
        char t = ans[i];
        ans[i] = ans[k - 1 - i];
        ans[k - 1 - i] = t;
    }

    free(temp);
    return ans;
}