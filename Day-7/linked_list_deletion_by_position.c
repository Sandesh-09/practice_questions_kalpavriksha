#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int id;
    char name[50];
    int age;
    struct Node *next;
} Node;

void loadUsers(Node **head)
{
    FILE *fp = fopen("users.txt", "r");

    if (fp == NULL)
    {
        fp = fopen("users.txt", "w");
        if (fp != NULL)
            fclose(fp);
        return;
    }

    Node *tail = NULL;
    int id, age;
    char name[50];

    while (fscanf(fp, "%d %49s %d", &id, name, &age) == 3)
    {
        Node *newNode = malloc(sizeof(Node));

        if (newNode == NULL)
        {
            fclose(fp);
            return;
        }

        newNode->id = id;
        newNode->age = age;
        snprintf(newNode->name, sizeof(newNode->name), "%s", name);
        newNode->next = NULL;

        if (*head == NULL)
            *head = newNode;
        else
            tail->next = newNode;

        tail = newNode;
    }

    fclose(fp);
}

int deleteAtPosition(Node **head, int pos)
{
    if (*head == NULL)
    {
        printf("Error: List is empty.\n");
        return 0;
    }

    if (pos < 1)
    {
        printf("Error: Invalid position.\n");
        return 0;
    }

    Node **cur = head;

    for (int i = 1; i < pos; i++)
    {
        if (*cur == NULL)
        {
            printf("Error: Invalid position.\n");
            return 0;
        }

        cur = &((*cur)->next);
    }

    if (*cur == NULL)
    {
        printf("Error: Invalid position.\n");
        return 0;
    }

    Node *temp = *cur;

    printf("Deleted: %d %s %d\n",
           temp->id, temp->name, temp->age);

    *cur = temp->next;

    free(temp);

    return 1;
}

void saveUsers(Node *head)
{
    FILE *fp = fopen("users.txt", "w");

    if (fp == NULL)
    {
        printf("Error: Cannot save file.\n");
        return;
    }

    Node *temp = head;

    while (temp != NULL)
    {
        fprintf(fp, "%d %s %d\n",
                temp->id, temp->name, temp->age);

        temp = temp->next;
    }

    fclose(fp);
}

void displayUsers(Node *head)
{
    if (head == NULL)
        return;

    Node *temp = head;

    while (temp != NULL)
    {
        printf("%d %s %d\n",
               temp->id, temp->name, temp->age);

        temp = temp->next;
    }
}

void freeList(Node *head)
{
    Node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    Node *head = NULL;
    int pos;

    loadUsers(&head);

    scanf("%d", &pos);

    int result = deleteAtPosition(&head, pos);

    if (result)
    {
        saveUsers(head);

        printf("Updated List:\n");
        displayUsers(head);
    }

    freeList(head);

    return 0;
}
