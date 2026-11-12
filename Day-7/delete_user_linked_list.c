/*
Delete User by ID (Pointer-to-Pointer)

Design a console-based program in C that loads users from users.txt, deletes a user by ID, and saves the updated list.

Requirements

Write loadUsers(Node **head) to read the file and build the list.
Write deleteById(Node **head, int id) using the pointer-to-pointer technique. Do not use a separate prev pointer and do not write a special case for the head node.
Return 1 if a node was deleted and 0 if the ID was not found.
Write saveUsers(Node *head) to rewrite users.txt.
Handle these edge cases: empty list, single-node list, deleting the head, deleting the tail, and an ID that does not exist.

Constraints: 0 ≤ N ≤ 100, IDs are unique positive integers.

Input Format

ID to delete

Output Format

User with ID <id> deleted.
Updated List:
<id> <name> <age>
...

Print List is empty. in place of the list if no users remain.

Sample Test Case 1

users.txt:
101 Asha 21
102 Ravi 25
103 Meena 30

Input:
102

Output:
User with ID 102 deleted.
Updated List:
101 Asha 21
103 Meena 30

Sample Test Case 2 (single node)

users.txt:
101 Asha 21

Input:
101

Output:
User with ID 101 deleted.
Updated List:
List is empty.

Sample Test Case 3 (ID not found)

users.txt:
101 Asha 21
102 Ravi 25

Input:
999

Output:
Error: User ID 999 not found.
Updated List:
101 Asha 21
102 Ravi 25

Sample Test Case 4 (empty file)

users.txt: (empty)

Input:
5

Output:
Error: List is empty.

*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int id;
    char name[50];
    int age;
    struct Node *next;
};

void addUsers()
{
    FILE *fp = fopen("users.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    int n;

    printf("Enter number of users: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int id, age;
        char name[50];

        printf("\nEnter details of user %d:\n", i + 1);

        printf("ID: ");
        scanf("%d", &id);

        printf("Name: ");
        scanf("%49s", name);

        printf("Age: ");
        scanf("%d", &age);

        fprintf(fp, "%d %s %d\n", id, name, age);
    }

    fclose(fp);

    printf("\nUser data saved successfully!\n");
}

void loadUsers(struct Node **head)
{
    FILE *fp = fopen("users.txt", "r");

    if (fp == NULL)
        return;

    struct Node *tail = NULL;

    int id, age;
    char name[50];

    while (fscanf(fp, "%d %49s %d", &id, name, &age) == 3)
    {
        struct Node *new_node = malloc(sizeof(struct Node));

        if (new_node == NULL)
            break;

        new_node->id = id;
        new_node->age = age;
        snprintf(new_node->name, sizeof(new_node->name), "%s", name);
        new_node->next = NULL;

        if (*head == NULL)
            *head = new_node;
        else
            tail->next = new_node;

        tail = new_node;
    }

    fclose(fp);
}

int deleteById(struct Node **head, int id)
{
    struct Node **cur = head;

    while (*cur != NULL)
    {
        if ((*cur)->id == id)
        {
            struct Node *temp = *cur;
            *cur = (*cur)->next;

            free(temp);
            return 1;
        }

        cur = &((*cur)->next);
    }

    return 0;
}

void saveUsers(struct Node *head)
{
    FILE *fp = fopen("users.txt", "w");

    if (fp == NULL)
    {
        printf("Error saving file!\n");
        return;
    }

    struct Node *temp = head;

    while (temp != NULL)
    {
        fprintf(fp, "%d %s %d\n",
                temp->id, temp->name, temp->age);

        temp = temp->next;
    }

    fclose(fp);
}

void displayUsers(struct Node *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = head;

    while (temp != NULL)
    {
        printf("ID: %d | Name: %s | Age: %d\n",
               temp->id, temp->name, temp->age);

        temp = temp->next;
    }
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
    struct Node *head = NULL;
    int id;

    addUsers();

    loadUsers(&head);

    printf("\nUsers before deletion:\n");
    displayUsers(head);

    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    if (deleteById(&head, id))
        printf("\nUser with ID %d deleted successfully.\n", id);
    else
        printf("\nUser ID %d not found.\n", id);

    saveUsers(head);

    printf("\nUpdated Users List:\n");
    displayUsers(head);

    freeList(head);

    return 0;
}
