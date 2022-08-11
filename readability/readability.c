#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h> 

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

int main(void) {    
    string text = get_string("Please input text: ");

    double index;
    double letters = count_letters(text);
    double words = count_words(text);
    double sentences = count_sentences(text);
    index = round(0.0588 * ((letters / words) * 100.0) - (0.296 * ((sentences / words) * 100.0)) - 15.8);

    if (index > 16) {
        printf("Grade 16+\n");
    }
    else if (index < 1) {
        printf("Before Grade 1\n");
    }
    else {
        printf("Grade %0.f\n", index);
    }
}

int count_letters(string text) {
    int numberOfLetters = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z' || text[i] >= 'A' && text[i] <= 'Z') {
            numberOfLetters++;
        }
    }

    return numberOfLetters;
}

int count_words(string text) {
    int numberOfWords;
    if (text[0] >= 'a' && text[0] <= 'z' || text[0] >= 'A' && text[0] <= 'Z') {
        numberOfWords = 1;
    }
    else {
        numberOfWords = 0;
    }
    
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == ' ') {
            numberOfWords++;
        }
    }

    return numberOfWords;
}

int count_sentences(string text) {
    int numberOfSentences = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            numberOfSentences++;
        }
    }

    return numberOfSentences;
}
