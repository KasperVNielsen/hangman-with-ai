#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "wordbank.h"

static int count = 0;             
static char wordlist[466471][64];   

void readList(){
   
    if (count == 0) {   
        char buffer[64];
              
        FILE *fptr = fopen("words2.txt", "r");

        if (fptr == NULL) { printf("no file\n"); exit(1); }

        while (count < 466471 && fgets(buffer, 64, fptr) != NULL) {

            // Remove newline characters
            buffer[strcspn(buffer, "\r\n")] = '\0';

            // Skip empty lines
            if (strlen(buffer) == 0) {
                 continue;
            }

            // Convert everything to lowercase
            for (int i = 0; buffer[i] != '\0'; i++) {
                buffer[i] = tolower((unsigned char)buffer[i]);
            }

            int valid = 1;

            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] < 'a' || buffer[i] > 'z') {
                    valid = 0;
                    break;
                }
            }

            if (!valid) {
                continue;
            }

            strcpy(wordlist[count], buffer);
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


