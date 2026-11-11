#include <stdlib.h>

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{

    struct ListNode *head = NULL;
    struct ListNode *tail = NULL;

    int carry = 0;

    while (l1 != NULL || l2 != NULL || carry != 0)
    {

        int sum = carry;

        if (l1 != NULL)
        {
            sum += l1->val;
            l1 = l1->next;
        }

        if (l2 != NULL)
        {
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10;

        // Dynamic memory allocation
        struct ListNode *newNode =
            (struct ListNode *)malloc(sizeof(struct ListNode));

        if (newNode == NULL)
        {
            return head;
        }

        newNode->val = sum % 10;
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}
