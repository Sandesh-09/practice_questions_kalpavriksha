#include <stdio.h>
#include <stdlib.h>

struct Node
{
    long long data;
    struct Node *next;
};

struct Node *createNode(long long value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
        return NULL;

    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

void insertEnd(struct Node **head, struct Node **tail, long long value)
{
    struct Node *newNode = createNode(value);

    if (newNode == NULL)
        return;

    if (*head == NULL)
    {
        *head = *tail = newNode;
        return;
    }

    (*tail)->next = newNode;
    *tail = newNode;
}

long long findMiddle(struct Node *head)
{
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow->data;
}

long long findKthFromEnd(struct Node *head, int k)
{
    struct Node *first = head;
    struct Node *second = head;

    for (int i = 0; i < k; i++)
    {
        if (first == NULL)
            return -1;

        first = first->next;
    }

    while (first != NULL)
    {
        first = first->next;
        second = second->next;
    }

    return second->data;
}

void freeList(struct Node *head)
{
    struct Node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    int n, k;

    struct Node *head = NULL;
    struct Node *tail = NULL;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        long long value;
        scanf("%lld", &value);

        insertEnd(&head, &tail, value);
    }

    scanf("%d", &k);

    long long middle = findMiddle(head);
    long long kth = findKthFromEnd(head, k);

    printf("%lld\n", middle);
    printf("%lld\n", kth);

    freeList(head);

    return 0;
}
