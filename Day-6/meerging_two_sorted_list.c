struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    struct ListNode dummy;
    dummy->next = NULL;

    struct ListNode *end = &dummy;

    while (list1 != NULL && list2 != NULL)
    {
        if (list1->val <= list2->val)
        {
            end->next = list1;
            list1 = list1->next;
        }
        else
        {
            end->next = list2;
            list2 = list2->next;
        }

        end = end->next;
    }

    if (list1 != NULL)
        end->next = list1;
    else
        end->next = list2;

    return dummy->next;
}
