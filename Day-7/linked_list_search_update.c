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
        strcpy(newNode->name, name);
        newNode->next = NULL;

        if (*head == NULL)
            *head = newNode;
        else
            tail->next = newNode;

        tail = newNode;
    }

    fclose(fp);
}

Node *searchById(Node *head, int id)
{
    Node *cur = head;

    while (cur != NULL)
    {
        if (cur->id == id)
            return cur;

        cur = cur->next;
    }

    return NULL;
}

int updateUser(Node *head, int id,
               const char *newName, int newAge)
{
    if (head == NULL)
    {
        printf("Error: List is empty.\n");
        return 0;
    }

    Node *found = searchById(head, id);

    if (found == NULL)
    {
        printf("Error: User ID %d not found.\n", id);
        return 0;
    }

    if (newAge < 1 || newAge > 120)
    {
        printf("Error: Invalid age. Record not updated.\n");
        return 0;
    }

    printf("Before: %d %s %d\n",
           found->id, found->name, found->age);

    strcpy(found->name, newName);
    found->age = newAge;

    printf("After: %d %s %d\n",
           found->id, found->name, found->age);

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

    Node *cur = head;

    while (cur != NULL)
    {
        fprintf(fp, "%d %s %d\n",
                cur->id, cur->name, cur->age);

        cur = cur->next;
    }

    fclose(fp);
}

void freeList(Node *head)
{
    Node *tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main()
{
    Node *head = NULL;

    int id, newAge;
    char newName[50];

    loadUsers(&head);

    scanf("%d", &id);
    scanf("%49s", newName);
    scanf("%d", &newAge);

    int result = updateUser(head, id, newName, newAge);

    if (result)
        saveUsers(head);

    freeList(head);

    return 0;
}
