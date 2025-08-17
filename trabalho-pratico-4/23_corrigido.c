#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

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

    int nonNull = 0;
    while (lists[nonNull] == NULL) {
        nonNull++;
        if (nonNull == listsSize)
            return NULL;
    }

    for (int i = nonNull + 1; i < listsSize; i++) {
        struct ListNode* toMerge = lists[i];
        while (toMerge != NULL) {
            struct ListNode* merged = lists[nonNull];
            while (merged != NULL) {
                if (toMerge->val < merged->val) {
                    struct ListNode *oldNext = merged->next;
                    int temp = merged->val;

                    merged->val = toMerge->val;
                    merged->next = malloc(sizeof(struct ListNode));

                    merged->next->val = temp;
                    merged->next->next = oldNext;
                    break;
                } else if (merged->next == NULL) {
                    merged->next = malloc(sizeof(struct ListNode));
                    merged->next->val = toMerge->val;
                    merged->next->next = NULL;
                    break;
                }

                merged = merged->next;
            }

            toMerge = toMerge->next;
        }
    }

    return lists[nonNull];
}