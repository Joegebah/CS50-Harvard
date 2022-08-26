#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <stdint.h>
 
 typedef uint8_t BYTE;
 const int BLOCK_SIZE = 512;

int main(int argc, char *argv[]) {
    bool inputIsValid = argc == 2 && (strcmp(argv[1], "card.raw")) == 0;
    
    if (!inputIsValid) {
        printf("Usage: ./recover card.raw\n");

        return 1;
    }

    FILE *recoveryCard = fopen(argv[1], "r");
    bool fileCannotBeRead = recoveryCard == NULL;

    if (fileCannotBeRead) {
        printf("File cannot be opened. Please try again. \n");

        return 1;
    }

    BYTE buffer;
    BYTE signatureBytes[4];
    signatureBytes[3] = signatureBytes[3] >> 4;
    char stringSize[4];
    int lastDigit = 0;
    int secondLastDigit = 0;
    int thirdLastDigit = 0;

    while (fread(&buffer, 1, BLOCK_SIZE, recoveryCard) == BLOCK_SIZE) {
        sprintf(stringSize, "%d%d%d.png", thirdLastDigit, secondLastDigit, lastDigit);
        printf("%s", stringSize);
        
        bool lastDigitHasOverflow = lastDigit > 9;
        bool secondDigitsHasOverflow = secondLastDigit > 9;

        if (lastDigitHasOverflow) {
            secondLastDigit++;
            lastDigit = 0;
        }

        if (secondDigitsHasOverflow) {
            thirdLastDigit++;
            secondLastDigit = 0;
        }

        fread(signatureBytes, sizeof(signatureBytes), 3, recoveryCard);
        FILE *output = fopen(stringSize, "w");

        if (signatureBytes[0] == 0xff && signatureBytes[1] == 0xd8 && signatureBytes[2] == 0xff && signatureBytes[3] == 0xe) {
            fwrite(&buffer, 1, BLOCK_SIZE, output);
        }

        lastDigit++;
    }

}
