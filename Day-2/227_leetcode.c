// Basic Calculator II

int calculate(char *s)
{
    int n = strlen(s);
    int *st = (int *)malloc(n * sizeof(int));

    int top = -1;
    int num = 0;
    char sign = '+';

    for (int i = 0; i < n; i++)
    {

        if (isdigit(s[i]))
        {
            num = num * 10 + (s[i] - '0');
        }

        if ((!isdigit(s[i]) && s[i] != ' ') || i == n - 1)
        {

            if (sign == '+')
            {
                st[++top] = num;
            }
            else if (sign == '-')
            {
                st[++top] = -num;
            }
            else if (sign == '*')
            {
                st[top] *= num;
            }
            else if (sign == '/')
            {
                st[top] /= num;
            }

            sign = s[i];
            num = 0;
        }
    }

    int ans = 0;

    while (top >= 0)
    {
        ans += st[top--];
    }

    free(st);
    return ans;
}
