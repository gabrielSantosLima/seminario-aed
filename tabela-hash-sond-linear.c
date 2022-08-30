#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 7

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



int hash(char *key)
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


int linearHashing(char *key, int i){
	
	return (hash(key)+i) % MAXSIZE;
	
}

void insert(HASHTABLE *table, char *key, char *name, int age, int rg)
{
    if (table->length == MAXSIZE)
        return;
    ITEM *newItem = createItem(key, name, age, rg);
    int collision = 0;
    while (table->data[linearHashing(key, collision)] != NULL)
    {
        collision++;
        printf("Colisao: de %s foi de %d para %d\n", name, linearHashing(key, (collision - 1)), linearHashing(key, collision));
    }
    table->data[linearHashing(key, collision)] = newItem;
    table->length++;
}

ITEM *findElementByKey(HASHTABLE table, char *key)
{
    int collision = 0;
    while (collision < MAXSIZE)
    {
        ITEM *item = table.data[linearHashing(key, collision)];
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
        ITEM *item = table->data[linearHashing(key, collision)];
        if (item != NULL && strcmp(item->key, key) == 0)
        {
            table->data[linearHashing(key, collision)] = NULL;
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
    insert(table, "Guilhermo ", "Guilhermo", 19, 99999999);
    insert(table, "Sabrina", "Sabrina", 19, 11111111);
    insert(table, "Alexandre", "Alexandre", 19, 44444444);
    //insert(table, "Luana M.", "Luana", 19, 88888888);
    printAll(*table);
    printf("\n");
    return 0;
}
