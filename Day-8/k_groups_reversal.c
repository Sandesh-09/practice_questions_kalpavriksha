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
    strcpy(newNode->name, name);
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

void reverseKIterative(Node **head, int k)
{
    Node *cur = *head;
    Node *prevGroup = NULL;
    Node *newHead = NULL;

    while (cur != NULL)
    {
        Node *check = cur;
        int cnt = 0;

        while (check != NULL && cnt < k)
        {
            check = check->next;
            cnt++;
        }

        if (cnt < k)
        {
            if (prevGroup != NULL)
            {
                prevGroup->next = cur;
            }
            break;
        }

        Node *groupStart = cur;
        Node *prev = NULL;
        Node *next = NULL;
        cnt = 0;

        while (cur != NULL && cnt < k)
        {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
            cnt++;
        }

        if (newHead == NULL)
        {
            newHead = prev;
        }

        if (prevGroup != NULL)
        {
            prevGroup->next = prev;
        }

        groupStart->next = cur;
        prevGroup = groupStart;
    }

    if (newHead != NULL)
    {
        *head = newHead;
    }
}

Node *reverseKRecursive(Node *head, int k)
{
    Node *check = head;
    int cnt = 0;

    while (check != NULL && cnt < k)
    {
        check = check->next;
        cnt++;
    }

    if (cnt < k)
    {
        return head;
    }

    Node *cur = head;
    Node *prev = NULL;
    Node *next = NULL;
    cnt = 0;

    while (cur != NULL && cnt < k)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        cnt++;
    }

    head->next = reverseKRecursive(cur, k);

    return prev;
}

void saveList(Node *head)
{
    FILE *fp = fopen("users_k.txt", "w");

    if (fp == NULL)
    {
        printf("Error: Unable to create users_k.txt\n");
        return;
    }

    while (head != NULL)
    {
        fprintf(fp, "%d %s %d\n", head->id, head->name, head->age);
        head = head->next;
    }

    fclose(fp);
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

    int k, choice;

    loadUsers(&head);

    int n = countNodes(head);

    if (n == 0)
    {
        printf("Error: List is empty.\n");
        return 0;
    }

    scanf("%d %d", &k, &choice);

    if (k < 1 || k > n)
    {
        printf("Error: Invalid k.\n");
        freeList(&head);
        return 0;
    }

    if (choice != 1 && choice != 2)
    {
        printf("Error: Invalid choice.\n");
        freeList(&head);
        return 0;
    }

    printf("Original List (%d users):\n", n);
    displayList(head);

    if (choice == 1)
    {
        reverseKIterative(&head, k);

        printf("List after reversing in groups of %d (Iterative):\n", k);
    }
    else
    {
        head = reverseKRecursive(head, k);

        printf("List after reversing in groups of %d (Recursive):\n", k);
    }

    displayList(head);

    saveList(head);

    freeList(&head);

    return 0;
}
