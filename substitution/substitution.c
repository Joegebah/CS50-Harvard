#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool hasLength(string s);
bool hasDigits(string s);
bool hasOnlyDefiniteLetters(string s);
char rotate(char c, string s);

int main(int argc, string argv[]) {

    bool isNotValidAmountOfArguments = argc != 2;

    if (isNotValidAmountOfArguments) {
        printf("Usage: Please enter a 26 a letter long string like ./caesar key\n");

        return 1;
    }

    string key = argv[1];
    bool hasRequiredLength = hasLength(key);
    bool hasDigitCharacters = hasDigits(key);
    bool hasDefiniteLetters = hasOnlyDefiniteLetters(key);
    bool inputIsValid = (hasRequiredLength == true) && (hasDigitCharacters == false) && (hasDefiniteLetters == true);
    bool inputIsInvalid = inputIsValid == false;

    if (inputIsInvalid) {
        printf("Usage: Please enter a 26 a letter long string like ./caesar key\n");

        return 1;
    }
    if (inputIsValid) {
        string plain = get_string("plain text: ");
        printf("ciphertext: ");

        for (int i = 0; i < plain[i]; i++) {
            printf("%c", rotate(plain[i], key));
        }
        printf("\n");

        return 0;
    }
}   

bool hasLength(string s) {
    if (strlen(s) == 26) return true;
    
    return false;
}

bool hasDigits(string s) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] >= '1' && s[i] <= '9') return true;
    }
    
    return false;
}

bool hasOnlyDefiniteLetters(string s) {
    for (int i = 0; i < strlen(s); i++) {
        for (int j = 0; j < strlen(s); j++) {
            if (i != j) {
                if (s[i] == s[j]) {

                return false;
                }
            }
        }
    }
    
    return true;
}

char rotate(char c, string s) {

    bool isInLowerAlphabet = (c >= 'a') && (c <= 'z');
    bool isInUpperAlphabet = (c >= 'A') && (c <= 'Z');

    if (isInLowerAlphabet) {

        int i = 0;
        char lowerAlphabetRotator = 'a';

        while (c != lowerAlphabetRotator) {
            lowerAlphabetRotator++;
            i++;
        }
        c = s[i];

        return c;
    }
    if (isInUpperAlphabet) {

        int i = 0;
        char lowerAlphabetRotator = 'A';

        while (c != lowerAlphabetRotator) {
            lowerAlphabetRotator++;
            i++;
        }
        c = s[i];

        return c;
    }

    return c;
}
