#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

#define MAX_WORD_LENGTH 30
#define MAX_LINE_LENGTH 1024

int main() {
    setlocale(LC_ALL,"");
    FILE *file = fopen("text.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    wchar_t line[MAX_LINE_LENGTH];
    wchar_t longestWord[MAX_WORD_LENGTH + 1] = L"";
    wchar_t currentWord[MAX_WORD_LENGTH + 1] = L"";
    wchar_t *words[MAX_LINE_LENGTH / 2];
    int wordCount = 0;

    while (fgetws(line, MAX_LINE_LENGTH, file)) {
        wchar_t *token = wcstok(line, L" \t\n()[]{};:,.<>\"\'!?");

        while (token != NULL) {
            int j = 0;
            for (int i = 0; token[i]; i++) {
                if (iswalpha(token[i]) && j < MAX_WORD_LENGTH) {
                    currentWord[j++] = token[i];
                }
            }
            currentWord[j] = L'\0';

            if (wcslen(currentWord) > 0) {
                if (wcslen(currentWord) > wcslen(longestWord)) {
                    wcscpy(longestWord, currentWord);
                }

                int found = 0;
                for (int i = 0; i < wordCount; i++) {
                    if (wcscmp(words[i], currentWord) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    words[wordCount] = wcsdup(currentWord);
                    wordCount++;
                }
            }

            token = wcstok(NULL, L" \t\n()[]{};:,.<>\"\'!?");
        }
    }

    fclose(file);

    FILE *outfile = fopen("output.txt", "w");
    if (outfile == NULL) {
        perror("Failed to open output file");
        return 1;
    }

    fwprintf(outfile, L"Longest word: %ls\n", longestWord);

    fwprintf(outfile, L"Words with the same length as the longest word:\n");
    for (int i = 0; i < wordCount; i++) {
        if (wcslen(words[i]) == wcslen(longestWord)) {
            fwprintf(outfile, L"%ls\n", words[i]);
        }
        free(words[i]);
    }

    fclose(outfile);

    return 0;
}
