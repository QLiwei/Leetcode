/*
 * @lc app=leetcode.cn id=1 lang=c
 *
 * [1] 两数之和
 */

// @lc code=start
#include <stdlib.h>
#include <stddef.h>

struct HashNode {
    int key;
    int value;
    struct HashNode* next; // 用于处理冲突的链表
};

struct HashTable {
    int size; // 哈希表的大小
    struct HashNode** array; // 存储指向哈希节点的指针的数组
};

struct HashTable* createHashTable(int size) {
    struct HashTable* table = (struct HashTable*)malloc(sizeof(struct HashTable));
    table->size = size;
    table->array = (struct HashNode**)malloc(sizeof(struct HashNode*) * size);

    // 初始化数组中的所有指针为 NULL
    for (int i = 0; i < size; i++) {
        table->array[i] = NULL;
    }

    return table;
}

int hashFunction(int key, int table_size) {
    return abs(key) % table_size;
}

void insert(struct HashTable* table, int key, int value) {
    int index = hashFunction(key, table->size);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    if (table->array[index] == NULL) {
        table->array[index] = newNode;
    } else {
        // 处理冲突，将新节点添加到链表的末尾
        struct HashNode* current = table->array[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int search(struct HashTable* table, int key) {
    int index = hashFunction(key, table->size);
    struct HashNode* current = table->array[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value; // 找到了键，返回相应的值
        }
        current = current->next;
    }
    return -1; // 未找到键
}

void destroyHashTable(struct HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        struct HashNode* current = table->array[i];
        while (current != NULL) {
            struct HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->array);
    free(table);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
#if 0
    for (int i = 0; i < numsSize; i++) {
        for (int j = numsSize - 1; j > i; j--) {
            if (nums[i] + nums[j] == target) {
                int *result = malloc(2 * sizeof(int));
                result[0] = i;
                result[1] = j;
                *returnSize = 2;
                return result;
            }
        }
    }
    *returnSize = 0;
    return 0;
#endif
    int *result = malloc(2 * sizeof(int));
    struct HashTable *table = createHashTable(256);
    for (int i = 0; i < numsSize; i++) {
        insert(table, nums[i], i);
    }

    for (int i = 0; i < numsSize; i++) {
        int value = target - nums[i];
        int index = search(table, value);
        if (index != -1 && index != i) {
            result[0] = i;
            result[1] = index;
            *returnSize = 2;
            destroyHashTable(table);
            return result;
        }
    }
    *returnSize = 0;
    destroyHashTable(table);
    return 0;
}
// @lc code=end