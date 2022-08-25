#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool hasLength(string key);
bool hasDigits(string key);
bool hasOnlyDefiniteLetters(string key);
char rotate(char plaintextCharToBeModified, string key);

int main(int argc, string argv[]) {

    bool isNotValidAmountOfArguments = argc != 2;

    if (isNotValidAmountOfArguments) {
        printf("Usage: ./substitution key\n");

        return 1;
    }

    string key = argv[1];
    bool hasRequiredLength = hasLength(key);
    bool hasDigitCharacters = hasDigits(key);
    bool hasDefiniteLetters = hasOnlyDefiniteLetters(key);
    bool inputIsValid = hasRequiredLength && !hasDigitCharacters && hasDefiniteLetters;

    if (!inputIsValid) {
        printf("Usage: Please enter a 26 a letter long string like ./substitution key\n");

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

bool hasLength(string key) {
    return strlen(key) == 26;

}

bool hasDigits(string key) {
    for (int i = 0; i < strlen(key); i++) {
        if (key[i] >= '0' && key[i] <= '9') return true;
    }
    
    return false;
}

bool hasOnlyDefiniteLetters(string key) {
    for (int i = 0; i < strlen(key); i++) {
        for (int j = 0; j < strlen(key); j++) {
            bool letterIsNotDefinite = (i != j) && (key[i] == key[j]);
            if (letterIsNotDefinite)  {

                return false;
            }
        }
    }

    return true;
}

char rotate(char plaintextCharToBeModified, string key) {

    bool isInLowerAlphabet = (plaintextCharToBeModified >= 'a') && (plaintextCharToBeModified <= 'z');
    bool isInUpperAlphabet = (plaintextCharToBeModified >= 'A') && (plaintextCharToBeModified <= 'Z');

    if (isInLowerAlphabet) {

        int i = 0;
        char lowerAlphabetRotator = 'a';

        while (plaintextCharToBeModified != lowerAlphabetRotator) {
            lowerAlphabetRotator++;
            i++;
        }
        plaintextCharToBeModified = tolower(key[i]);
    }

    if (isInUpperAlphabet) {

        int i = 0;
        char lowerAlphabetRotator = 'A';

        while (plaintextCharToBeModified != lowerAlphabetRotator) {
            lowerAlphabetRotator++;
            i++;
        }
        plaintextCharToBeModified = toupper(key[i]);
    }

    return plaintextCharToBeModified;
}
