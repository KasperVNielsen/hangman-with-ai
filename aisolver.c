#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wordbank.h"
#include <string.h>

static bool wordMatcher(char* word, char* missedLetters, int missedCount, char* pattern){
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
                    if (pattern[j] != '_' && word[i] == pattern[j]) 
                        return false;   
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

static char frequencyChooser(char* candidates[],int candidateCount, char* pattern){
    int countPerLetter[26] = {0};
    
    for(int i = 0; i < candidateCount; i++){
        bool isCounted[26] = {false};
        
        for(int j = 0;candidates[i][j] != '\0';j++){
            int index = candidates[i][j] - 'a';

            if(!isCounted[index]){
                countPerLetter[index]++;
                isCounted[index] = true;
            }
        }
    }

    int bestSlot = -1;
    int highest = 0;
    
    for(int i = 0; i < 26;i++){
        char letter = 'a' + i;
        bool guessed = false;

        for(int j = 0; pattern[j] !='\0';j++){
            if(pattern[j] == letter){
                guessed = true;
            }
        }

        if(!guessed && countPerLetter[i] > highest){

            highest = countPerLetter[i];
            bestSlot = i;
        }
    }
    
    if(bestSlot == -1)
        return '\0';

    return 'a' + bestSlot;
}

char bestGuess(char* pattern, char* missedLetters, int missedCount) {

    static char* candidates[466471];

    int count = getCount();
    int picksCount = 0;

    // Filter possible words
    for (int i = 0; i < count; i++) {

        char* word = getWord(i);

        if (wordMatcher(word, missedLetters, missedCount,pattern)) {

            candidates[picksCount] = word;
            picksCount++;
        }
    }

    // No candidates found
    if (picksCount == 0) {
        return '\0';
    }

    // Choose the most frequent unguessed letter
    return frequencyChooser(
        candidates,
        picksCount,
        pattern
    );
}