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
int counterOfWordsInDict = 0;
node *table[N];

bool check(const char *word) {
    int bucketIndex = hash(word);
    node *cursor = table[bucketIndex];
    
    while (cursor != NULL) {
        if (strcasecmp(cursor->word, word) == 0) {
            return true;
        } 
            
        cursor = cursor->next;
    }

    return false;
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
    
    char dictWord[LENGTH + 1];
    while (fscanf(dict, "%s", dictWord) != EOF) {  
        node *newNode = malloc(sizeof(node));
        
        if (newNode == NULL) {

            return false;
        }

        strcpy(newNode->word, dictWord);
        unsigned int bucketIndex = hash(dictWord);

        bool bucketIsEmpty = table[bucketIndex] == NULL;
        if (bucketIsEmpty) {
            newNode->next = NULL;
        }
        else {
            newNode->next = table[bucketIndex];
        }

        table[bucketIndex] = newNode;
        counterOfWordsInDict++;
    }

    fclose(dict);

    return true;
}

unsigned int size(void) {
    return counterOfWordsInDict;
}

bool unload(void) {
    for (int linkedListIterator = 0; linkedListIterator < N; linkedListIterator++) {
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
