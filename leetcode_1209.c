//  Remove All Adjacent Duplicates in String II

char *removeDuplicates(char *s, int k)
{
    int n = strlen(s);

    char *st = (char *)malloc((n + 1) * sizeof(char));
    int *cnt = (int *)malloc((n + 1) * sizeof(int));
    int top = -1;

    for (int i = 0; i < n; i++)
    {
        if (top != -1 && st[top] == s[i])
        {
            top++;
            st[top] = s[i];
            cnt[top] = cnt[top - 1] + 1;
        }
        else
        {
            top++;
            st[top] = s[i];
            cnt[top] = 1;
        }

        if (cnt[top] == k)
        {
            top -= k;
        }
    }

    st[top + 1] = '\0';
    free(cnt);

    return st;
}