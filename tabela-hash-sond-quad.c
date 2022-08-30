#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 11

typedef struct ITEM
{
    char *key;
    char *name;
    int age;
    int rg;

} ITEM;

typedef struct HASHTABLE
{
    int length;
    ITEM *data[MAXSIZE];

} HASHTABLE;

ITEM *createItem(char *key, char *name, int age, int rg)
{
    ITEM *newNode = (ITEM *)malloc(sizeof(ITEM));
    newNode->key = (char *)malloc(strlen(key));
    newNode->name = (char *)malloc(strlen(name));
    strcpy(newNode->key, key);
    strcpy(newNode->name, name);
    newNode->age = age;
    newNode->rg = rg;
    return newNode;
}

// The function createHashTable will be a vector which is inicialized with null
HASHTABLE *createHashTable()
{
    HASHTABLE *newHashTable = (HASHTABLE *)malloc(sizeof(HASHTABLE));
    newHashTable->length = 0;
    for (int index = 0; index < MAXSIZE; index++)
    {
        newHashTable->data[index] = NULL;
    }
    return newHashTable;
}

// The hash function must recieve a key (char string)
// and will return the position where that key will be allocated

int hash(char *key)
{
    int length = strlen(key);
    int index = 0;
    int hashKey = 0;
    for (index = 0; index < length; index++)
    {
        int charKey = (int)key[index];
        hashKey += 13 * (charKey * charKey);
    }
    return hashKey % MAXSIZE;
}

int quadraticHashing(char *key, int i)
{
    return (hash(key) + 2 * i + 3 * (i * i)) % MAXSIZE;
}

void insert(HASHTABLE *table, char *key, char *name, int age, int rg)
{
    if (table->length == MAXSIZE)
        return;
    ITEM *newItem = createItem(key, name, age, rg);
    int collision = 0;
    while (table->data[quadraticHashing(key, collision)] != NULL)
    {
        collision++;
        printf("Colisao: de %s foi de %d para %d\n", name, quadraticHashing(key, (collision - 1)), quadraticHashing(key, collision));
    }
    table->data[quadraticHashing(key, collision)] = newItem;
    table->length++;
}

ITEM *findElementByKey(HASHTABLE table, char *key)
{
    int collision = 0;
    while (collision < MAXSIZE)
    {
        ITEM *item = table.data[quadraticHashing(key, collision)];
        if (item != NULL && strcmp(item->key, key) == 0)
            return item;
        collision++;
    }
    return NULL;
}

void removeElementByKey(HASHTABLE *table, char *key)
{
    if (table->length == 0)
        return;
    int collision = 0;
    while (collision < MAXSIZE)
    {
        ITEM *item = table->data[quadraticHashing(key, collision)];
        if (item != NULL && strcmp(item->key, key) == 0)
        {
            table->data[quadraticHashing(key, collision)] = NULL;
            table->length--;
            free(item);
            return;
        }
        collision++;
    }
}

void printAll(HASHTABLE table)
{
    int index = 0;
    for (index = 0; index < MAXSIZE; index++)
    {
        ITEM *item = table.data[index];
        if (item != NULL)
        {
            printf("%d: %s is [name=%s, age=%d, rg=%d]\n",
                   index,
                   item->key,
                   item->name,
                   item->age,
                   item->rg);
        }
        else
        {
            printf("%d: VAZIO\n", index);
        }
    }
}

int main()
{
    HASHTABLE *table = createHashTable();
    // insert(table, "Gabriel", "Gabriel", 19, 22222222);
    // insert(table, "Arthur", "Arthur", 19, 33333333);
    insert(table, "Alexandre", "Alexandre", 19, 44444444);
    // insert(table, "Lídia", "Lídia", 19, 55555555);
    //insert(table, "Augusto", "Augusto", 19, 66666666);
    //insert(table, "Roberto", "Roberto", 19, 77777777);
    insert(table, "Guilhermo ", "Guilhermo", 19, 99999999);
    insert(table, "Luana M.", "Luana", 19, 88888888);
    // insert(table, "Adriano", "Adriano", 19, 21221212);
    insert(table, "Sabrina", "Sabrina", 19, 11111111);
    printAll(*table);
    printf("\n");

    return 0;
}