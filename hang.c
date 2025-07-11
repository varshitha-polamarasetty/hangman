#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_TRIES 6
#define WORD_COUNT 10

// Predefined list of words – you can expand this!
const char *wordList[WORD_COUNT] = {
    "apple", "banana", "laptop", "hangman", "code",
    "guitar", "dragon", "castle", "rocket", "planet"
};

int main() {
    srand(time(0)); // Seed random number
    const char *word = wordList[rand() % WORD_COUNT]; // Pick random word

    int wordLen = strlen(word);
    char display[wordLen + 1];
    char guessedLetters[26] = "";

    int i, correct = 0, wrong = 0;

    // Initialize display word with underscores
    for (i = 0; i < wordLen; i++) {
        display[i] = '_';
    }
    display[wordLen] = '\0';

    printf("🎮 Welcome to Hangman (Random Word Edition)!\n");
    printf("Guess the word chosen by the computer!\nYou have %d chances.\n\n", MAX_TRIES);

    while (wrong < MAX_TRIES && correct < wordLen) {
        printf("Word: ");
        for (i = 0; i < wordLen; i++) {
            printf("%c ", display[i]);
        }

        char guess;
        printf("\nGuess a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        // Check if already guessed
        int alreadyGuessed = 0;
        for (i = 0; i < strlen(guessedLetters); i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }

        if (alreadyGuessed) {
            printf("⚠️ Already guessed '%c'. Try something new.\n\n", guess);
            continue;
        }

        // Add to guessed letters
        int len = strlen(guessedLetters);
        guessedLetters[len] = guess;
        guessedLetters[len + 1] = '\0';

        // Check if guess is correct
        int found = 0;
        for (i = 0; i < wordLen; i++) {
            if (word[i] == guess && display[i] == '_') {
                display[i] = guess;
                correct++;
                found = 1;
            }
        }

        if (!found) {
            wrong++;
            printf("❌ Wrong! %d tries left.\n\n", MAX_TRIES - wrong);
        } else {
            printf("✅ Nice! '%c' is in the word.\n\n", guess);
        }
    }

    if (correct == wordLen) {
        printf("🎉 Yay! You guessed it: %s\n", word);
    } else {
        printf("💀 Oh no! The word was: %s\n", word);
    }

    return 0;
}
