#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ALPHABET_LOWER[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char ALPHABET_UPPER[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',  'X', 'Y', 'Z'};

int main(int argc, string argv[])  {

    bool isValidInput = argc != 2;
    if (isValidInput) {
        printf("Usage: Please enter a single number as a key. Like this: ./caesar key\n");

        return 1;
    }

    int key = atoi(argv[1]) % 26;

    if (key < 1) {
        printf("Usage: Please enter a single number as a key. Like this: ./caesar key\n");

        return 1;
    }

    string plain = get_string("plaintext: "); 

    for (int i = 0; i < strlen(argv[1]); i++) {
        if (argv[1][i] < 'a' && argv[1][i] > 'z' || argv[1][i] < 'A' && argv[1][i] > 'Z') {
            printf("Usage: Please enter a single number higher than 0 as a key. Like this: ./caesar key\n");

            return 1;
        }
    }

    for (int i = 0; i < strlen(plain); i++) {
        for (int j = 0; j < sizeof(ALPHABET_LOWER); j++) {

            bool isInAlphabets = plain[i] == ALPHABET_LOWER[j] || plain[i] == ALPHABET_UPPER[j];
            bool isNotInAlphabets = plain[i] < 'a' && plain[i] > 'z' || plain[i] < 'A' && plain[i] > 'Z';
            int overflow;
            bool overflowIsFixed = false;

            if (isInAlphabets) {
                plain[i] = plain[i] + key;
                
                break;
            }
            
            if ((plain[i] + key) > 'z') {
                overflow = 0;
                while (isInAlphabets) {
                plain[i] = plain[i] + key;
                overflow++;
                }
                plain[i] = 'a' + (key - overflow);
                break;
                
            }
            else if ((plain[i] + key) > 'Z') {
                overflow = 0;
                while (isInAlphabets) {
                plain[i] = plain[i] + key;
                overflow++;
                }
                plain[i] = 'A' + (key - overflow);
                break;
            }
        }
    }   
    printf("ciphertext:  %s\n", plain);

    return 0;
}
