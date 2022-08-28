#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 23

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
    ITEM *newItem = (ITEM *)malloc(sizeof(ITEM));
    newItem->key = (char *)malloc(strlen(key));
    newItem->name = (char *)malloc(strlen(name));
    strcpy(newItem->key, key);
    strcpy(newItem->name, name);
    newItem->age = age;
    newItem->rg = rg;
    return newItem;
}

HASHTABLE *createHashTable()
{
    HASHTABLE *newHashTable = (HASHTABLE *)malloc(sizeof(HASHTABLE));
    newHashTable->length = 0;
    int index = 0;
    for (index = 0; index < MAXSIZE; index++)
    {
        newHashTable->data[index] = NULL;
    }
    return newHashTable;
}

int hash67Of(char *key)
{
    int length = strlen(key);
    int index = 0;
    int hashKey = 0;
    for (index = 0; index < length; index++)
    {
        int charKey = (int)key[index];
        hashKey += 67 * (charKey * charKey);
    }
    return hashKey % MAXSIZE;
}

int hash31Of(char *key)
{
    int length = strlen(key);
    int index = 0;
    int hashKey = 0;
    for (index = 0; index < length; index++)
    {
        int charKey = (int)key[index];
        hashKey += 31 * (charKey * charKey * charKey);
    }
    return hashKey % MAXSIZE;
}

int doubleHashing(char *key, int i)
{
    return (hash67Of(key) + i * hash31Of(key)) % MAXSIZE;
}

void insert(HASHTABLE *table, char *key, char *name, int age, int rg)
{
    if (table->length == MAXSIZE)
        return;
    ITEM *newItem = createItem(key, name, age, rg);
    int collision = 0;
    while (table->data[doubleHashing(key, collision)] != NULL)
    {
        collision++;
    }
    table->data[doubleHashing(key, collision)] = newItem;
    table->length++;
}

ITEM *findElementByKey(HASHTABLE table, char *key)
{
    int collision = 0;
    while (collision < MAXSIZE)
    {
        ITEM *item = table.data[doubleHashing(key, collision)];
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
        ITEM *item = table->data[doubleHashing(key, collision)];
        if (item != NULL && strcmp(item->key, key) == 0)
        {
            table->data[doubleHashing(key, collision)] = NULL;
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
    insert(table, "Gabriel", "Gabriel", 19, 22222222);
    insert(table, "Arthur", "Arthur", 19, 33333333);
    insert(table, "Alexandre", "Alexandre", 19, 44444444);
    insert(table, "Lídia", "Lídia", 19, 55555555);
    insert(table, "Augusto", "Augusto", 19, 66666666);
    insert(table, "Roberto", "Roberto", 19, 77777777);
    insert(table, "Luana", "Luana", 19, 88888888);
    insert(table, "Guilhermo", "Guilhermo", 19, 99999999);
    insert(table, "Adriano", "Adriano", 19, 21221212);
    insert(table, "Sabrina", "Sabrina", 19, 11111111);
    insert(table, "Sergio", "Sergio", 30, 12121212);
    printAll(*table);
    printf("\n");
    removeElementByKey(table, "Sergio");
    printAll(*table);
    printf("\n");
    ITEM *item = findElementByKey(*table, "Gabriel");
    if (item == NULL)
    {
        printf("Item não encontrado");
    }
    else
    {
        printf("%s is [name=%s, age=%d, rg=%d]\n", item->key, item->name, item->age, item->rg);
    }
    return 0;
}