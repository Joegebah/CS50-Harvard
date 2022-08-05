#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char ALPHABET_LOWER[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char ALPHABET_UPPER[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int compute_score(string word);

int main(void) {
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
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
    // TODO: Compute and return score for string
    int scoreCount = 0;
    for (int i = 0, n = strlen(word); i < n; i++) {
        for (int j = 0, cl = ALPHABET_LOWER[j],cu = ALPHABET_UPPER[j]; j < sizeof(ALPHABET_LOWER); j++) {
            if (word[i] == ALPHABET_LOWER[j] || word[i] == ALPHABET_UPPER[j]) {
                scoreCount = scoreCount + POINTS[j];
            }
        }
    }
return scoreCount;
       /*  if (word[i] == 'a' || word[i] == 'A') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'b' || word[i] == 'B') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'c' || word[i] == 'C') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'd' || word[i] == 'D') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'e' || word[i] == 'E') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'f' || word[i] == 'F') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'g' || word[i] == 'G') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'h' || word[i] == 'H') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'i' || word[i] == 'I') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'j' || word[i] == 'J') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'k' || word[i] == 'K') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'l' || word[i] == 'L') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'm' || word[i] == 'M') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'n' || word[i] == 'N') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'o' || word[i] == 'O') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'p' || word[i] == 'P') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'q' || word[i] == 'Q') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'r' || word[i] == 'R') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 's' || word[i] == 'S') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 't' || word[i] == 'T') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'u' || word[i] == 'U') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'v' || word[i] == 'V') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'w' || word[i] == 'W') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'x' || word[i] == 'X') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'y' || word[i] == 'Y') {
            scoreCount = scoreCount + POINTS[1];
        }
        if (word[i] == 'z' || word[i] == 'Z') {
            scoreCount = scoreCount + POINTS[1];
        } */
}
