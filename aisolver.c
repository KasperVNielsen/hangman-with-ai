#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wordbank.h"
#include <string.h>

bool wordMatcher(char* word, char* missedLetters, int missedCount, char* pattern){
       int length = strlen(pattern);
       
       //rule one match length
       if(strlen(word) != length)
            return false;

       for (int i = 0; i < length; i++) {

            // Rule 2: Revealed positions must match
            if (pattern[i] != '_' && pattern[i] != word[i])
                return false;

            // Rule 3: Revealed letters cannot be hidden
            if (pattern[i] == '_') {
                for (int j = 0; j < length; j++) {
                    if (pattern[j] != '_' && word[i] == pattern[j]) {
                        return false;
                    }
                }
            }

            

            // Rule 4: No missed letters
            for(int j = 0; j < missedCount;j++){
                if(word[i] == missedLetters[j])
                    return false;
        }

    }
    return true;
}

char frequencyChooser(char* candidates[],int candidateCount){
    int countPerLetter[26] = {0};

    for(int i = 0; i < candidateCount; i++){
        for(int j = 0;candidates[i][j] != '\0';j++){
            int index = candidates[i][j] - 'a';
            countPerLetter[index]++;
        }
    }
}

int main(){
    readList();     
    int count = getCount();
    
    char pattern[] = "_________";

    char missedLetters[26];
    int missedCount = 0;

    static char* candidates[60000];
    int pickCount = 0;
    
    for (int i = 0; i < count; i++) {
        char* word = getWord(i);

        if (wordMatcher(word, missedLetters, missedCount, pattern )) { 
           if(pickCount < 60000){
               candidates[pickCount] = word;
               pickCount++;
           } 
           else{ break;}
        }
        frequencyChooser(candidates,pickCount);
    }

    printf("Candidates: %d\n", pickCount);
    printf("First few: ");
    for (int i = 0; i < pickCount && i < 5; i++)
        printf("%s ", candidates[i]);
    printf("\nMiddle: ");
    if (pickCount > 0)
        printf("%s ", candidates[pickCount / 2]);
    printf("\nLast few: ");
    for (int i = pickCount - 5 < 0 ? 0 : pickCount - 5; i < pickCount; i++)
        printf("%s ", candidates[i]);
    printf("\n");

      printf("loaded: %d\n", getCount());
printf("[%s] len=%zu\n", getWord(0),      strlen(getWord(0)));
printf("[%s] len=%zu\n", getWord(5000),   strlen(getWord(5000)));
printf("[%s] len=%zu\n", getWord(getCount()-1), strlen(getWord(getCount()-1)));

}