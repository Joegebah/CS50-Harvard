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

    if (recoveryCard == NULL) {
        printf("File cannot be opened. Please try again. \n");

        return 2;
    }

    BYTE blockOfBytesOfInput[BLOCK_SIZE];
    int imageCounter = 0;

    FILE *outputImage = NULL;
    char *fileName = malloc(8 * sizeof(char));

    while (fread(blockOfBytesOfInput, 1, BLOCK_SIZE, recoveryCard)) {

        bool signatureIsEncountered = blockOfBytesOfInput[0] == 0xff && blockOfBytesOfInput[1] == 0xd8 && blockOfBytesOfInput[2] == 0xff && ((blockOfBytesOfInput[3] & 0xf0) == 0xe0);

        if (signatureIsEncountered) {
            sprintf(fileName ,"%03i.jpg", imageCounter);
            outputImage = fopen(fileName, "w");
            imageCounter++;
        }
        
        if(outputImage != NULL) {
            fwrite(blockOfBytesOfInput, 1, BLOCK_SIZE, outputImage);            
        }
    }

    free(fileName);
    fclose(outputImage);
    fclose(recoveryCard);

    return 0;
}
