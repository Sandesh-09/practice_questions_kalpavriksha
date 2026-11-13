#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int id;
    char name[50];
    int age;
    struct Node *next;
} Node;

Node *createNode(int id, char name[], int age)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->id = id;
    snprintf(newNode->name, sizeof(newNode->name), "%s", name);
    newNode->age = age;
    newNode->next = NULL;

    return newNode;
}

void loadUsers(Node **head)
{
    FILE *fp = fopen("users.txt", "r");

    if (fp == NULL)
    {
        return;
    }

    Node *tail = NULL;
    int id, age;
    char name[50];

    while (fscanf(fp, "%d %49s %d", &id, name, &age) == 3)
    {
        Node *newNode = createNode(id, name, age);

        if (*head == NULL)
        {
            *head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(fp);
}

int countNodes(Node *head)
{
    int cnt = 0;

    while (head != NULL)
    {
        cnt++;
        head = head->next;
    }

    return cnt;
}

void displayList(Node *head)
{
    while (head != NULL)
    {
        printf("%d %s %d\n", head->id, head->name, head->age);
        head = head->next;
    }
}

void reverseIterative(Node **head)
{
    Node *prev = NULL;
    Node *curr = *head;
    Node *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    *head = prev;
}

Node *reverseRecursive(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    Node *newHead = reverseRecursive(head->next);

    head->next->next = head;
    head->next = NULL;

    return newHead;
}

void saveReversedList(Node *head)
{
    FILE *fp = fopen("users_reversed.txt", "w");

    if (fp == NULL)
    {
        printf("Error: Unable to create users_reversed.txt\n");
        return;
    }

    while (head != NULL)
    {
        fprintf(fp, "%d %s %d\n", head->id, head->name, head->age);
        head = head->next;
    }

    fclose(fp);
}

int verifyList(Node *head, Node original[], int n)
{
    int i = 0;

    while (head != NULL && i < n)
    {
        if (head->id != original[i].id ||
            head->age != original[i].age ||
            strcmp(head->name, original[i].name) != 0)
        {
            return 0;
        }

        head = head->next;
        i++;
    }

    return head == NULL && i == n;
}

void freeList(Node **head)
{
    Node *temp;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main()
{
    Node *head = NULL;
    Node original[100];

    int choice;

    loadUsers(&head);

    printf("Enter choice (1 = Iterative, 2 = Recursive): ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2)
    {
        printf("Error: Invalid choice.\n");
        freeList(&head);
        return 0;
    }

    int n = countNodes(head);

    if (n == 0)
    {
        printf("Error: List is empty. Nothing to reverse.\n");
        freeList(&head);
        return 0;
    }

    Node *temp = head;

    for (int i = 0; i < n; i++)
    {
        original[i].id = temp->id;
        original[i].age = temp->age;
        snprintf(original[i].name, sizeof(original[i].name), "%s", temp->name);

        temp = temp->next;
    }

    printf("\nOriginal List (%d users):\n", n);
    displayList(head);

    if (choice == 1)
    {
        reverseIterative(&head);

        printf("\nReversed List (Iterative):\n");
        displayList(head);

        saveReversedList(head);

        head = reverseRecursive(head);

        if (verifyList(head, original, n))
        {
            printf("Verification: Original order restored using Recursive.\n");
        }
        else
        {
            printf("Verification: Failed.\n");
        }
    }
    else
    {
        head = reverseRecursive(head);

        printf("\nReversed List (Recursive):\n");
        displayList(head);

        saveReversedList(head);

        reverseIterative(&head);

        if (verifyList(head, original, n))
        {
            printf("Verification: Original order restored using Iterative.\n");
        }
        else
        {
            printf("Verification: Failed.\n");
        }
    }

    freeList(&head);

    return 0;
}
