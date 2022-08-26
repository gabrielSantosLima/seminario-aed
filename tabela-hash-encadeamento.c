#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 10

typedef struct NODE
{
    int value;
    char *key;
    struct NODE *nextNode;
} NODE;

typedef struct HASHTABLE
{
    NODE *data[MAXSIZE];
} HASHTABLE;

int hash(char *key)
{
    int length = strlen(key);
    int index = 0;
    int hashKey = 0;
    for (index = 0; index < length; index++)
    {
        int charKey = (int)key[index];
        int charIntegerExpression = pow(64, length - 1 - index);
        long result = charKey * charIntegerExpression;
        hashKey += result;
    }
    return hashKey % MAXSIZE;
}

NODE *createNode(char *key, int value)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->key = (char *)malloc(strlen(key));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->nextNode = NULL;
    return newNode;
}

HASHTABLE *createHashTable()
{
    HASHTABLE *newHashTable = (HASHTABLE *)malloc(sizeof(HASHTABLE));
    int index = 0;
    for (index = 0; index < MAXSIZE; index++)
    {
        newHashTable->data[index] = NULL;
    }
    return newHashTable;
}

void add(HASHTABLE *hashTable, char *key, int value)
{
    NODE *newNode = createNode(key, value);
    if (hashTable->data[hash(key)] == NULL)
    {
        hashTable->data[hash(key)] = newNode;
    }
    else
    {
        NODE *tempNode = hashTable->data[hash(key)];
        while (tempNode->nextNode != NULL)
        {
            tempNode = tempNode->nextNode;
        }
        tempNode->nextNode = newNode;
    }
}

NODE *find(HASHTABLE *hashTable, char *key)
{
    NODE *node = hashTable->data[hash(key)];
    if (node == NULL)
        return NULL;
    if (strcmp(node->key, key) != 0)
    {
        while (node->key != key)
        {
            node = node->nextNode;
        }
    }
    return node;
}

void removeByKey(HASHTABLE *hashTable, char *key)
{
    NODE *node = hashTable->data[hash(key)];
    if (node == NULL)
        return;
    if (strcmp(node->key, key) == 0)
    {
        NODE *tempNode = hashTable->data[hash(key)];
        hashTable->data[hash(key)] = tempNode->nextNode;
        free(tempNode);
    }
    else
    {
        NODE *tempNode = hashTable->data[hash(key)];
        NODE *lastTempNode = NULL;
        while (tempNode != NULL && strcmp(tempNode->key, key) != 0)
        {
            lastTempNode = tempNode;
            tempNode = tempNode->nextNode;
        }
        if (tempNode == NULL)
            return;
        lastTempNode->nextNode = tempNode->nextNode;
        free(tempNode);
    }
}

void printAllNode(NODE *node)
{
    while (node != NULL)
    {
        printf("> Elemento: '%s' para %d\n", node->key, node->value);
        node = node->nextNode;
    }
}

void printAll(HASHTABLE *hashTable)
{
    int index = 0;
    for (index = 0; index < MAXSIZE; index++)
    {
        printf("\n>>> %d\n", index);
        if (hashTable->data[index] != NULL)
        {
            printAllNode(hashTable->data[index]);
        }
        else
        {
            printf("Vazio\n");
        }
    }
}

int main()
{
    HASHTABLE *hashTable = createHashTable();
    add(hashTable, "C++", 19);
    add(hashTable, "C++", 50);
    add(hashTable, "AWK", 20);
    removeByKey(hashTable, "C++");
    printAll(hashTable);
    return 0;
}