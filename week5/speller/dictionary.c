#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "dictionary.h"

typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 26;
node *table[N];

bool check(const char *word) {
    

    return false;
}

unsigned int hash(const char *word) {
    
    return toupper(word[0]) - 'A';
}

bool load(const char *dictionary) {
    
    
    return false;
}

unsigned int size(void) {
    
    return 0;
}

bool unload(void) {
    
    return false;
}
