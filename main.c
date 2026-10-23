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
   static char wordlist[1000][20];   
    static int count = 0;             

    if (count == 0) {                 
        FILE *fptr = fopen("words.txt", "r");
        if (fptr == NULL) { printf("no file\n"); exit(1); }
        while (count < 1000 && fgets(wordlist[count], 20, fptr) != NULL) {
            wordlist[count][strcspn(wordlist[count], "\n")] = '\0'; 
            count++;
        }
        fclose(fptr);
    }

    return wordlist[rand() % count];
}

void gameLoop(){
    
    int lives = 6;
    char guess;
    char* answer = selectWord();

    int lenght = strlen(answer);
    char shown[20];
    printf("%s\n", answer);

    while (1)
    {
        printf("%s\n", shown);
        printf("Lives: %d\n", lives);

        printf("Type a letter: ");
        scanf(" %c", &guess);  

        for (int i = 0; i < lenght; i++) shown[i] = '_';
            shown[lenght] = '\0';
        

        int hit = 0;
        for (int i = 0; i < lenght; i++) {
            if (answer[i] == guess) {
                shown[i] = guess;
                hit = 1;
            }
        }

        if(!hit){
            lives--;
            printf("you didnt hit");

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