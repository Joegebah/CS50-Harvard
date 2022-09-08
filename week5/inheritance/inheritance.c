
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cs50.h>

typedef struct person {
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *person, int generation);
void free_family(person *person);
char random_allele();

int main(void) {
    srand(time(0));
    person *person = create_family(GENERATIONS);
    print_family(person, 0);
    free_family(person);
}

person *create_family(int generations) {
    person *createdPerson = malloc(sizeof(person));

    if (generations > 1) {
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);
        
        createdPerson->parents[0] = parent0;
        createdPerson->parents[1] = parent1;

        int randomIntForAllele = rand() % 2;
        createdPerson->alleles[0] = parent0->alleles[randomIntForAllele];
        createdPerson->alleles[1] = parent1->alleles[randomIntForAllele];
    }
    else {
        createdPerson->parents[0] = NULL;
        createdPerson->parents[1] = NULL;

        createdPerson->alleles[0] = random_allele();
        createdPerson->alleles[1] = random_allele();
    }

    return createdPerson;
}

void free_family(person *person) {
    if (person == NULL) {

        return;
    }

    free_family(person->parents[0]);
    free_family(person->parents[1]);
    free(person);
}

void print_family(person *person, int generation) {
    if (person == NULL) {
        return;
    }

    for (int i = 0; i < generation * INDENT_LENGTH; i++) {
        printf(" ");
    }

    switch (generation) {
        case 0:
            printf("Child (Generation %i): blood type %c%c\n", generation, person->alleles[0], person->alleles[1]);
            break;
        case 1:
            printf("Parent (Generation %i): blood type %c%c\n", generation, person->alleles[0], person->alleles[1]);
            break;
        default:
            for (int i = 0; i < generation - 2; i++) {
                printf("Great-");
            }

            printf("Grandparent (Generation %i): blood type %c%c\n", generation, person->alleles[0], person->alleles[1]);
            break;
    }

    print_family(person->parents[0], generation + 1);
    print_family(person->parents[1], generation + 1);
}

char random_allele() {
    int r = rand() % 3;
    switch(r) {
        case 0:
            return 'A';
        case 1:
            return 'B';
        default: 
            return 'O';
    }
}
