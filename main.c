#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "wordbank.h"

struct word {
    char *text;  
    //lives  
    int difficulty; 
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
    char shown[32];
    //printf("%s\n", answer);

    for (int i = 0; i < lenght; i++) shown[i] = '_';
            shown[lenght] = '\0';
    while (1)
    {
        printf("%s\n", shown);
        printf("Lives: %d\n", lives);

        printf("Type a letter: ");
        scanf(" %c", &guess);  

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

            if(lives == 0){
                printf("You lost. The word was: %s\n", answer);
                break;
            }
        }

        if (strcmp(shown, answer) == 0) {
            printf("You won! The word was: %s\n", answer);
            break;
        }
    }
}

int main(void){
    srand(time(NULL));

    
    gameLoop();
    return 0;
}