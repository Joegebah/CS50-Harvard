#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char ALPHABET_LOWER[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char ALPHABET_UPPER[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int compute_score(string word);

int main(void) {

    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2) {
        printf("Player 1 has won, congratulations!");
    }
    else if (score1 < score2) {
        printf("Player 2 has won, congratulations!");
    }
    else {
        printf("Tie!");
    }
}

int compute_score(string word) {
    int scoreCount = 0;
    for (int i = 0, n = strlen(word); i < n; i++) {
        for (int j = 0, cl = ALPHABET_LOWER[j],cu = ALPHABET_UPPER[j]; j < sizeof(ALPHABET_LOWER); j++) {
            if (word[i] == ALPHABET_LOWER[j] || word[i] == ALPHABET_UPPER[j]) {
                scoreCount = scoreCount + POINTS[j];
            }
        }
    }
    
return scoreCount;
}