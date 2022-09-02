#include <stdio.h>
#include <string.h>
#include <cs50.h>

#define MAX 9

int preferences[MAX][MAX];
bool locked[MAX][MAX];

typedef struct {
    int winner;
    int loser;
}
pair;

string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int get_rank_index(int candidateNumber, int ranks[]);

int main(int argc, string argv[]) {
    bool thereIsNoCandidateInput = argc < 2;

    if (thereIsNoCandidateInput) {
        printf("Usage: tideman [candidate ...]\n");

        return 1;
    }

    candidate_count = argc - 1;
    bool candidateOverflow = candidate_count > MAX;

    if (candidateOverflow) {
        printf("Maximum number of candidates is %i\n", MAX);

        return 2;
    }

    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++) {
        candidates[candidateIndex] = argv[candidateIndex + 1];
    }

    for (int rowIterator = 0; rowIterator < candidate_count; rowIterator++) {
        for (int columnIterator = 0; columnIterator < candidate_count; columnIterator++) {
            locked[rowIterator][columnIterator] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    for (int voterIterator = 0; voterIterator < voter_count; voterIterator++) {
        int ranks[candidate_count];

        for (int candidateRank = 0; candidateRank < candidate_count; candidateRank++) {
            string name = get_string("Rank %i: ", candidateRank + 1);
            bool voteIsInvalid = !vote(candidateRank, name, ranks);

            if (voteIsInvalid) {
                printf("Invalid vote.\n");

                return 3;
            }
        }
       
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    return 0;
}

bool vote(int candidateRank, string name, int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        bool candidateIsValid = strcmp(candidates[i], name) == 0;

        if (candidateIsValid) {
            ranks[candidateRank] = i;

            return true;
        }
    }

    return false;
}

void record_preferences(int ranks[]) {
    for (int rowIterator = 0; rowIterator < candidate_count; rowIterator++) {
        for (int columnIterator = 0; columnIterator < candidate_count; columnIterator++) {
            int firstCompareCandidate = rowIterator;
            int secondCompareCandidate = columnIterator;
            int indexOfFirstCompareCandidate = get_rank_index(firstCompareCandidate, ranks);
            int indexOfSeconCompareCandidate = get_rank_index(secondCompareCandidate, ranks);
            bool candidateIsPreferred = indexOfFirstCompareCandidate < indexOfSeconCompareCandidate;

            if (candidateIsPreferred) {
                preferences[rowIterator][columnIterator]++;
            }
        }
    }

    return;
}

void add_pairs(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            pair pair;
            bool candidateIIsWinner = preferences[i][j] > preferences[j][i];
            bool candidateJIsWinner = preferences[i][j] < preferences[j][i];

            if (candidateIIsWinner) {
                pair.winner = i;
                pair.loser = j;
            }
            else if (candidateJIsWinner) {
                pair.winner = j;
                pair.loser = i;
            }
            
            pairs[pair_count] = pair;
            pair_count++;
        }
    }

    return;
}

void sort_pairs(void) {
    for (int amountOfIterationsIndex = 0; amountOfIterationsIndex < pair_count; amountOfIterationsIndex++) {
        for (int pairIterator = 0; pairIterator < pair_count; pairIterator++) {
            int pairWinnerIndex = pairs[pairIterator].winner;
            int pairLoserIndex = pairs[pairIterator].loser;
            int nextPairWinnerIndex = pairs[pairIterator + 1].winner; 
            int nextPairLoserIndex = pairs[pairIterator + 1].loser;
            int thisStrengthOfVictory = preferences[pairWinnerIndex][pairLoserIndex];
            int nextStrengthOfVictory = preferences[nextPairWinnerIndex][nextPairLoserIndex];

            bool nextCandidateHasGreaterStrength = thisStrengthOfVictory < nextStrengthOfVictory;

            if (nextCandidateHasGreaterStrength) {
                pair savePairFromOverride = pairs[pairIterator];
                pairs[pairIterator] = pairs[pairIterator + 1];
                pairs[pairIterator + 1] = savePairFromOverride;
            }
        }
    }

    return;
}

void lock_pairs(void) {
    for (int pairIterator = 0; pairIterator < pair_count; pairIterator++) {
        int rowNumberForLocked = pairs[pairIterator].winner;
        int columnNumberForLocked = pairs[pairIterator].loser;

        locked[rowNumberForLocked][columnNumberForLocked] = true;

        for (int columnIterator = 0; columnIterator < candidate_count; columnIterator++) {

            bool columnHasFalse = false;

            for (int rowIterator = 0; rowIterator < candidate_count; rowIterator++)  {
                int rowMax = candidate_count - 1;
                bool columnIsChecked = rowIterator == rowMax;
                bool cellIsTrue = locked[columnIterator][rowIterator] == true;
                int countColumnsWithTrue = 0;
                bool allColumsHaveAtLeastOneTrueInThem = countColumnsWithTrue == candidate_count - 1;
                bool columnHasOnlyFalse = columnIsChecked && !cellIsTrue;


                if (cellIsTrue) {
                    countColumnsWithTrue++;
                    columnIterator++;

                    break;
                }
                
                if (columnHasOnlyFalse) { 
                    columnHasFalse = true;    

                    break;
                }

                if (allColumsHaveAtLeastOneTrueInThem) {
                    locked[rowNumberForLocked][columnNumberForLocked] = false;

                    return; 
                }
            }

            if (columnHasFalse) {
                
                break;
            }
        }
    } 

    return;
}

void print_winner(void) {
    int columnIterator = 0;

    while (columnIterator < candidate_count) {
        int rowIterator = 0;

        while (rowIterator < candidate_count) {
            int rowMax = candidate_count - 1;
            bool cellIsTrue = locked[rowIterator][columnIterator] == true;
            bool columnIsThrough = rowIterator == rowMax;
            bool columnHasOnlyFalse = columnIsThrough && !cellIsTrue;


            if (cellIsTrue) {
                columnIterator++;

                break;
            }

            if (columnHasOnlyFalse) {
                printf("The winner is: %s\n", candidates[columnIterator]);

                return;
            }

            rowIterator++;
        }
    }
}

int get_rank_index(int candidateNumber, int ranks[]) {
    int rankIndex;
    for (int candidateIterator = 0; candidateIterator < candidate_count; candidateIterator++) {
        bool candidateIsFound = ranks[candidateIterator] == candidateNumber;

        if (candidateIsFound) {
            rankIndex = candidateIterator;
        }
    }

    return rankIndex;
}
