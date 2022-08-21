#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

typedef struct {
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];

int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[]) {
    if (argc < 2) {
        printf("Usage: plurality [candidate ...]\n");

        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);

        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++) {

        string name = get_string("Vote: ");

        if (!vote(name)) {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
    return 0;
}

bool vote(string name) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            candidates[i].votes++;

            return true;
        }
    }

    return false;
}

void print_winner(void) {

    int i = 0;

    while (i < candidate_count - 1) {
        for (int i = 0; i < candidate_count - 1; i++) {

            if (candidates[i].votes < candidates[i + 1].votes) {

                candidate save = candidates[i];
                candidates[i] = candidates[i + 1];
                candidates[i + 1] = save;
            }
        }
        i++;
    }
    if (candidates[0].votes != candidates[1].votes) {
        printf("%s has won the election!\n", candidates[0].name);
    }
    else {
        
        i = 0;

        printf("The winners are: \n");
        while (i < candidate_count) {

            int maximumVote = candidates[0].votes; 
            bool hasFoundMaxVotes = candidates[i].votes == maximumVote;

            if (hasFoundMaxVotes) {
                printf("%s \n", candidates[i].name);
            }
            i++;
        }
    }

    return;
}
