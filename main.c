#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 30
#define MAX_LINE_LENGTH 1024

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char longestWord[MAX_WORD_LENGTH + 1] = "";
    char currentWord[MAX_WORD_LENGTH + 1] = "";
    char *words[MAX_LINE_LENGTH / 2];

    file = fopen("text.txt", "r");          

    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    int wordCount = 0;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, " \t\n()[]{};:,.<>\"\'!?");  

        while (token != NULL) {               
            int j = 0;
            for (int i = 0; token[i]; i++) {
                if (isalpha(token[i]) && j < MAX_WORD_LENGTH) {
                    currentWord[j++] = token[i];  
                }
            }
            currentWord[j] = '\0';              

            if (strlen(currentWord) > 0) {       
                if (strlen(currentWord) > strlen(longestWord)) {
                    strcpy(longestWord, currentWord);  
                }

                int found = 0;
                for (int i = 0; i < wordCount; i++) {
                    if (strcmp(words[i], currentWord) == 0) {
                        found = 1;                    
                        break;
                    }
                }
                if (!found) {
                    words[wordCount] = strdup(currentWord);  
                    wordCount++;
                }
            }

            token = strtok(NULL, " \t\n()[]{};:,.<>\"\'!?");  
        }
    }

    fclose(file);                            

    printf("Longest word: %s\n", longestWord);  

    printf("Words with the same length as the longest word:\n");
    for (int i = 0; i < wordCount; i++) {
        if (strlen(words[i]) == strlen(longestWord)) {
            printf("%s\n", words[i]);         
        }
        free(words[i]);                       
    }

    return 0;                                 
}
