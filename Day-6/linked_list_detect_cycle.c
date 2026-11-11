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

struct Node *detectCycle(struct Node *head)
{
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return slow;
    }

    return NULL;
}

int cycleLength(struct Node *meetingPoint)
{
    int count = 1;

    struct Node *temp = meetingPoint->next;

    while (temp != meetingPoint)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

void removeCycle(struct Node *head, struct Node *meetingPoint)
{
    struct Node *p1 = head;
    struct Node *p2 = meetingPoint;

    while (p1 != p2)
    {
        p1 = p1->next;
        p2 = p2->next;
    }

    struct Node *last = p1;

    while (last->next != p1)
    {
        last = last->next;
    }

    last->next = NULL;
}

void display(struct Node *head)
{
    struct Node *temp = head;

    while (temp != NULL)
    {
        printf("%lld", temp->data);

        if (temp->next != NULL)
            printf(" ");

        temp = temp->next;
    }

    printf("\n");
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
    int n, pos;

    struct Node *head = NULL;
    struct Node *tail = NULL;

    scanf("%d", &n);

    struct Node **nodes = (struct Node **)malloc(n * sizeof(struct Node *));

    if (nodes == NULL)
        return 1;

    for (int i = 0; i < n; i++)
    {
        long long value;
        scanf("%lld", &value);

        nodes[i] = createNode(value);

        if (nodes[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(nodes[j]);

            free(nodes);
            return 1;
        }

        if (head == NULL)
            head = tail = nodes[i];
        else
        {
            tail->next = nodes[i];
            tail = nodes[i];
        }
    }

    scanf("%d", &pos);

    if (pos != -1)
    {
        tail->next = nodes[pos];
    }

    struct Node *meetingPoint = detectCycle(head);

    if (meetingPoint == NULL)
    {
        printf("NO\n");
        printf("0\n");
    }
    else
    {
        printf("YES\n");

        int length = cycleLength(meetingPoint);
        printf("%d\n", length);

        removeCycle(head, meetingPoint);
    }

    display(head);
    freeList(head);
    free(nodes);

    return 0;
}
