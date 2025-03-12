#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TABLE_SIZE 10

typedef struct HashTable
{
    char key[100];
} HashTable;

HashTable ht[TABLE_SIZE];

void initializationHT()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        strcpy(ht[i].key, "");
    }
}

int midSquareHash(int key)
{
    int squared = key * key;
    int mid = (squared / 100) % 100;
    return mid % TABLE_SIZE;
}

int foldingHash(int key)
{
    int sum = 0;
    while (key > 0)
    {
        sum += key % 100;
        key /= 100;
    }
    return sum % TABLE_SIZE;
}

int digitExtractionHash(int key)
{
    return (key / 10) % TABLE_SIZE;
}

int rotatingHash(int key)
{
    int rotated = (key >> 2) | (key << (sizeof(int) * 8 - 2));
    return abs(rotated) % TABLE_SIZE;
}

int linearProbing(int index)
{
    int i = 0;
    while (strcmp(ht[(index + i) % TABLE_SIZE].key, "") != 0)
    {
        i++;
    }
    return (index + i) % TABLE_SIZE;
}

void insertLinear(char key[], int (*hashFunction)(int))
{
    int intKey = atoi(key);
    int index = hashFunction(intKey);
    if (strcmp(ht[index].key, "") != 0)
    {
        index = linearProbing(index);
    }
    strcpy(ht[index].key, key);
    printf("Key %s dimasukkan ke index %d dengan Linear Probing.\n", key, index);
}

void displayHT()
{
    printf("\nHash Table\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (strcmp(ht[i].key, "") != 0)
        {
            printf("Index %d: %s\n", i, ht[i].key);
        }
        else
        {
            printf("Index %d: Kosong\n", i);
        }
    }
}

int main()
{
    initializationHT();
    int choice;
    char key[100];
    int (*hashFunction)(int) = NULL;
    
    while (1)
    {
        printf("\n=== MENU ===\n");
        printf("1. Pilih Hash Function\n");
        printf("2. Pilih Collision Handling\n");
        printf("3. Masukkan Key\n");
        printf("4. Tampilkan Hash Table\n");
        printf("5. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Pilih Hash Function:\n1. Mid-Square\n2. Folding\n3. Digit Extraction\n4. Rotating Hash\n");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                hashFunction = midSquareHash;
                break;
            case 2:
                hashFunction = foldingHash;
                break;
            case 3:
                hashFunction = digitExtractionHash;
                break;
            case 4:
                hashFunction = rotatingHash;
                break;
            default:
                printf("Pilihan tidak valid!\n");
            }
            break;
        case 2:
            printf("Pilih Collision Handling:\n1. Linear Probing (default)\n");
            break;
        case 3:
            if (hashFunction == NULL)
            {
                printf("Harap pilih Hash Function terlebih dahulu!\n");
                break;
            }
            printf("Masukkan key (angka): ");
            scanf("%s", key);
            insertLinear(key, hashFunction);
            break;
        case 4:
            displayHT();
            break;
        case 5:
            exit(0);
        default:
            printf("Pilihan tidak valid!\n");
        }
    }
    return 0;
}
