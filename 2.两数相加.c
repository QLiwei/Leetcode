/*
 * @lc app=leetcode.cn id=2 lang=c
 *
 * [2] 两数相加
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/* 其他解法: 递归...*/
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    int carry = 0;
    struct ListNode* head = malloc(sizeof(struct ListNode));
    struct ListNode* node = head;

    while (l1 != NULL || l2 != NULL) {
        int sum = 0;
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }
        sum += carry;
        carry = sum / 10;

        node->next = malloc(sizeof(struct ListNode));
        node = node->next;
        node->val = sum % 10;
    }

    if (carry != 0) {
        node->next = malloc(sizeof(struct ListNode));
        node = node->next;
        node->val = carry;
    }

    node->next = NULL;
    return head->next;
}
// @lc code=end

