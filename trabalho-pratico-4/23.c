#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize < 1)
        return NULL;

    for (int i = 1; i < listsSize; i++) {
        struct ListNode* toMerge = lists[i];
        while (toMerge->next != NULL) {
            struct ListNode* merged = lists[0];
            while (merged->next != NULL) {
                if (toMerge->val >= merged->val) {
                    struct ListNode* oldNext = merged->next;
                    merged->next = toMerge;
                    merged->next->next = oldNext;
                }

                merged = merged->next;
            }

            toMerge = toMerge->next;
        }
    }

    return lists[0];
}