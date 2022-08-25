#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

const int HEADER_SIZE = 44;
typedef uint8_t BYTE;
typedef int16_t DOUBLE_BYTE;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    BYTE headerOfInput[HEADER_SIZE];
    fread(headerOfInput, HEADER_SIZE, 1, input);
    fwrite(headerOfInput, HEADER_SIZE, 1, output);

    DOUBLE_BYTE buffer;
    while (fread(&buffer, sizeof(DOUBLE_BYTE), 1, input)) {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(DOUBLE_BYTE), 1, output);
    }
    fclose(input);
    fclose(output);
}
