#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <cs50.h>

typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 26;
node *table[N];

bool check(const char *word) {
    int bucketIndex = hash(word);
    node *cursor = malloc(sizeof(node));
    cursor = table[bucketIndex];
    string s = cursor->word;
    printf("%s",s);
    bool linkedListHasReachedEnd = cursor == NULL;
    bool wordIsFound = strcasecmp(cursor->word, word) == 0;
    printf("test");
    bool checkIsValid = wordIsFound && !linkedListHasReachedEnd;
    
    while (!wordIsFound || !linkedListHasReachedEnd) {
        cursor = cursor->next;
    }

    free(cursor);
    return (checkIsValid) ? true : false;
}

unsigned int hash(const char *word) {
    
    return toupper(word[0]) - 'A';
}

bool load(const char *dictionary) {
    FILE *dict = fopen(dictionary, "r");
    
    bool canNotOpenFile = dict == NULL;

    if (canNotOpenFile) {
        printf("Could not open file.");

        return 1;
    }

    string word = malloc(sizeof(string));
    while (fscanf(dict, "%s", word) != EOF) {  
        node *newNode = malloc(sizeof(node));
        
        if (newNode == NULL) {

            return false;
        }
        
        strcpy(newNode->word, word);
        newNode->next = NULL;

        unsigned int bucketIndex = hash(newNode->word);
        bool bucketIsEmpty = table[bucketIndex] == NULL;
        if (bucketIsEmpty) {
            table[bucketIndex] = newNode;
        }
        else {
            newNode = table[bucketIndex]->next;
            table[bucketIndex] = newNode;
        }
    }

    free(word);

    return true;
}

unsigned int size(void) {
    int counter = 0; 

    for (int linkedListIterator = 0; linkedListIterator < N - 1; linkedListIterator++) {
        while (table[linkedListIterator]->next != NULL) {
            counter++;
        }
    }

    return counter;
}

bool unload(void) {
    for (int linkedListIterator = 0; linkedListIterator < N - 1; linkedListIterator++) {
        node *cursor = table[linkedListIterator]->next;
        node *tmp = cursor;
        while (cursor != NULL) {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }

    return true;
}
