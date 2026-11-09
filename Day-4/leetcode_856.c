int scoreOfParentheses(char *s)
{
    int n = strlen(s);

    int *st = (int *)malloc((n + 1) * sizeof(int));
    int top = -1;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
        {
            st[++top] = 0;
        }
        else
        {
            int cur = st[top--];

            int val = (cur == 0) ? 1 : 2 * cur;

            if (top == -1)
            {
                st[++top] = val;
            }
            else
            {
                st[top] += val;
            }
        }
    }
    int ans = st[0];
    free(st);
    return ans;
}