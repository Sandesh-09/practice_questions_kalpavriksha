/*

Problem Statement
Implement a singly linked list from scratch (in C, using struct and malloc) and process a sequence of commands on it. The list is empty at the start.
Requirements
•	Command "1 x": insert x at the head.
•	Command "2 x": insert x at the tail.
•	Command "3 p x": insert x so that it becomes the node at 0-based position p (0 <= p <= current size).
•	Command "4 x": delete the first node whose value is x; do nothing if x is not present.
•	Command "5 p": delete the node at 0-based position p; do nothing if p is out of range.
•	Command "6": print the list on one line, values separated by single spaces, or print EMPTY if the list is empty.
•	Use only linked nodes for storage (no array) and free deleted nodes.
Input Format
The first line contains an integer q, the number of commands.
Each of the next q lines contains one command in the formats above.
Constraints
•	1 <= q <= 10^4
•	-10^9 <= x <= 10^9
•	0 <= p <= 10^4
Output Format
For every command of type 6, print the current state of the list on its own line.
Sample Input 0
8
1 5
2 7
2 9
3 1 6
6
4 7
5 0
6

Sample Output 0
5 6 7 9
6 9

Explanation: The list evolves as [5], [5 7], [5 7 9], [5 6 7 9]; deleting 7 gives [5 6 9] and deleting position 0 gives [6 9].
Sample Input 1
3
1 3
4 3
6

Sample Output 1
EMPTY

Edge Cases to Handle
•	Deleting the head node and deleting the tail node.
•	Inserting at position 0 and at position equal to the size.
•	Deleting a value that appears several times (only the first occurrence goes).
•	Printing an empty list.
•	Deleting the only node (head and tail pointers must both be updated).
Concepts Tested
Node structure, dynamic memory allocation, traversal with prev/curr pointers, head and tail edge cases, freeing memory.

*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

void insertAtHead(struct Node **head, struct Node **tail, int value)
{
    struct Node *newNode = createNode(value);

    newNode->next = *head;
    *head = newNode;

    if (*tail == NULL)
    {
        *tail = newNode;
    }
}

void insertAtTail(struct Node **head, struct Node **tail, int value)
{
    struct Node *newNode = createNode(value);

    if (*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
        return;
    }

    (*tail)->next = newNode;
    *tail = newNode;
}

void insertAtPosition(struct Node **head, struct Node **tail,
                      int position, int value)
{
    if (position < 0)
    {
        return;
    }

    if (position == 0)
    {
        insertAtHead(head, tail, value);
        return;
    }

    struct Node *curr = *head;
    int i = 0;

    while (curr != NULL && i < position - 1)
    {
        curr = curr->next;
        i++;
    }

    if (curr == NULL)
    {
        return;
    }

    struct Node *newNode = createNode(value);

    newNode->next = curr->next;
    curr->next = newNode;

    if (newNode->next == NULL)
    {
        *tail = newNode;
    }
}

void deleteByValue(struct Node **head, struct Node **tail, int value)
{
    struct Node *curr = *head;
    struct Node *prev = NULL;

    while (curr != NULL && curr->data != value)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        return;
    }

    if (prev == NULL)
    {
        *head = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }

    if (curr == *tail)
    {
        *tail = prev;
    }

    free(curr);
}

void deleteAtPosition(struct Node **head, struct Node **tail, int position)
{
    if (*head == NULL || position < 0)
    {
        return;
    }

    struct Node *curr = *head;
    struct Node *prev = NULL;
    int i = 0;

    while (curr != NULL && i < position)
    {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (curr == NULL)
    {
        return;
    }

    if (prev == NULL)
    {
        *head = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }

    if (curr == *tail)
    {
        *tail = prev;
    }

    free(curr);
}

void display(struct Node *head)
{
    if (head == NULL)
    {
        printf("Empty\n");
        return;
    }

    struct Node *temp = head;

    while (temp != NULL)
    {
        printf("%d", temp->data);

        if (temp->next != NULL)
        {
            printf(" ");
        }

        temp = temp->next;
    }

    printf("\n");
}

void freeList(struct Node **head, struct Node **tail)
{
    struct Node *temp;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
}

int main()
{
    struct Node *head = NULL;
    struct Node *tail = NULL;

    int q, command;
    int x, p;

    scanf("%d", &q);

    while (q--)
    {
        scanf("%d", &command);

        switch (command)
        {
        case 1:
            scanf("%d", &x);
            insertAtHead(&head, &tail, x);
            break;

        case 2:
            scanf("%d", &x);
            insertAtTail(&head, &tail, x);
            break;

        case 3:
            scanf("%d %d", &p, &x);
            insertAtPosition(&head, &tail, p, x);
            break;

        case 4:
            scanf("%d", &x);
            deleteByValue(&head, &tail, x);
            break;

        case 5:
            scanf("%d", &p);
            deleteAtPosition(&head, &tail, p);
            break;

        case 6:
            display(head);
            break;
        }
    }

    freeList(&head, &tail);

    return 0;
}
