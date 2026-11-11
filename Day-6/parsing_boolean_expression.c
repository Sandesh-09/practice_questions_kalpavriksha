#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parsing_exp(char *exp)
{
    char st[10005];
    int top = -1;

    for (int i = 0; exp[i] != '\0'; i++)
    {

        char ch = exp[i];

        if (ch == ',')
        {
            continue;
        }

        if (ch == ')')
        {
            int cnt1 = 0;
            int cnt2 = 0;

            while (top != -1 && st[top] != '(')
            {
                if (st[top] == 't')
                {
                    cnt1++;
                }
                else if (st[top] == 'f')
                {
                    cnt2++;
                }
                top--;
            }

            top--;
            char op = st[top--];
            char ans;

            if (op == '!')
            {
                ans = (cnt1 == 1) ? 't' : 'f';
            }
            else if (op == '&')
            {
                ans = (cnt2 == 0) ? 't' : 'f';
            }
            else
            {
                ans = (cnt1 > 0) ? 't' : 'f';
            }

            st[++top] = ans;
        }
        else
        {
            st[++top] = ch;
        }
    }

    return st[top] == 't';
}
