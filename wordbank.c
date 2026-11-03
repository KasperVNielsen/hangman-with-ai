#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "wordbank.h"

static int count = 0;             
static char wordlist[466471][64];   

void readList(){
   
    if (count == 0) {                 
        FILE *fptr = fopen("words2.txt", "r");

        if (fptr == NULL) { printf("no file\n"); exit(1); }

        while (count < 466471 && fgets(wordlist[count], 64, fptr) != NULL) {
            // Remove newline characters
            wordlist[count][strcspn(wordlist[count], "\r\n")] = '\0';

             // Skip empty lines
            if (strlen(wordlist[count]) == 0) {
                continue;
            }
            if(strlen(wordlist[count]) < 3)
                continue;
            
            // Convert everything to lowercase
            for (int i = 0; wordlist[count][i] != '\0'; i++) {
                wordlist[count][i] = tolower((unsigned char)wordlist[count][i]);
            }

         

            // Validate word
            int valid = 1;

            for (int i = 0; wordlist[count][i] != '\0'; i++) {
                if (wordlist[count][i] < 'a' || wordlist[count][i] > 'z') {
                    valid = 0;
                    break;
                }
            }

            if (!valid) {
                continue;
            }

            count++;
        }
        fclose(fptr);
    }
}

int getCount(){
    return count;
}

char* getWord(int index){
    if (index < 0 || index >= count){
         printf("index not correct");
         return NULL;         
    }
    return wordlist[index];   
}


