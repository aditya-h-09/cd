#include <stdio.h>
#include <string.h>
#include <ctype.h>


int isReservedWord(char *word) {
    char reservedWords[][20] = {"auto", "break", "case", "char", "const", "continue", "default",
                                "do", "double", "else", "enum", "extern", "float", "for", "goto",
                                "if", "int", "long", "register", "return", "short", "signed", "sizeof",
                                "static", "struct", "switch", "typedef", "union", "unsigned", "void",
                                "volatile", "while"};

    int numReservedWords = sizeof(reservedWords) / sizeof(reservedWords[0]);

    for (int i = 0; i < numReservedWords; i++) {
        if (strcmp(word, reservedWords[i]) == 0) {
            return 1; 
        }
    }

    return 0; 
}


int isValidIdentifierChar(char ch) {
    return isalnum(ch) || ch == '_';
}


void scanIdentifiers(char *code) {
    char buffer[50];
    int i, j;

    for (i = 0; code[i] != '\0'; i++) {

        while (!isValidIdentifierChar(code[i]) && code[i] != '\0') {
            i++;
        }


        for (j = 0; isValidIdentifierChar(code[i]) && code[i] != '\0'; i++, j++) {
            buffer[j] = code[i];
        }

        buffer[j] = '\0';


        if (strlen(buffer) > 0) {
            if (isReservedWord(buffer)) {
                printf("Reserved Word: %s\n", buffer);
            } else {
                printf("Identifier: %s\n", buffer);
            }
        }
    }
}

int main() {
    char userInput[1000];

    printf("Enter C code:\n");
    fgets(userInput, sizeof(userInput), stdin);

    scanIdentifiers(userInput);

    return 0;
}
