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
        printf("Grade 16+");
    }
    else if (index < 1) {
        printf("Before Grade 1");
    }
    else {
        printf("Grade %0.f", index);
    }
}

int count_letters(string s) {
    int numberOfLetters = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z') {
            numberOfLetters++;
        }
    }

    return numberOfLetters;
}

int count_words(string s) {
    int numberOfWords;
    if (s[0] >= 'a' && s[0] <= 'z' || s[0] >= 'A' && s[0] <= 'Z') {
        numberOfWords = 1;
    }
    else {
        numberOfWords = 0;
    }
    
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == ' ') {
            numberOfWords++;
        }
    }

    return numberOfWords;
}

int count_sentences(string s) {
    int numberOfSentences = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?') {
            numberOfSentences++;
        }
    }

    return numberOfSentences;
}
