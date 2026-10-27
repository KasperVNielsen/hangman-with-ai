#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct word {
    char *text;  
    //lives  
    int difficulty; 
};

char * selectWord(){ 
   static char wordlist[466471][64];   
   static int count = 0;             
   
    if (count == 0) {                 
        FILE *fptr = fopen("words2.txt", "r");
        if (fptr == NULL) { printf("no file\n"); exit(1); }
        while (count < 466471 && fgets(wordlist[count], 64, fptr) != NULL) {
            wordlist[count][strcspn(wordlist[count], "\n")] = '\0'; 
            count++;
        }
        fclose(fptr);
    }
    long number= ((long)rand() << 15) | rand();
    return wordlist[number % count + 1];
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