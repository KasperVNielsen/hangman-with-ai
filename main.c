#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

#include "aisolver.h"
#include "wordbank.h"

struct word {
    char *text;  
    //might come later the higer the difficulty less lives and harder words
    int difficulty
};

char* selectWord(){ 
    readList();
    long number= ((long)rand() << 15) | rand();
    int index = number % getCount();
    return getWord(index);
}

void gameLoop(){  
    int lives = 6;
    char guess;
    char* answer = selectWord();

    int lenght = strlen(answer);
    char shown[64];
    char missedLetters[26];
    int missedCount = 0;
    //printf("%s\n", answer);

    for (int i = 0; i < lenght; i++) shown[i] = '_';
            shown[lenght] = '\0';

    while (1)
    {
        printf("%s\n", shown);
        printf("Lives: %d\n", lives);

        printf("Type a letter:\n ");
        guess = bestGuess(shown, missedLetters, missedCount);

        printf("ai guesses: %c ",guess);

        if(guess =='\0'){
            printf("no candidates");
            break;
        }

        int hit = 0;
        for (int i = 0; i < lenght; i++) {
            if (answer[i] == guess) {
                shown[i] = guess;
                
                hit = 1;
            }
        }

        if(!hit){
            lives--;
            printf("you didnt hit\n");

            missedLetters[missedCount] = guess;
            missedCount++;

            if(lives == 0){
                printf("You lost. The word was: %s\n", answer);
                break;
            }
        }

        if (strcmp(shown, answer) == 0) {
            printf("\nYou won! The word was: %s\n", answer);
            break;
        }
        Sleep(800);
    }
}

int main(void){
    srand(time(NULL));

    gameLoop();
    return 0;
}