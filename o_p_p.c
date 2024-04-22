#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printErrorMessage() {
    printf("Not operator grammar");
    exit(0);
}

int main() {
    char grammar[20][20], symbol;
    int i, numProductions, j = 2, isValid = 0;

    printf("Enter the number of production rules: ");
    scanf("%d", &numProductions);

    // Reading the production rules
    for (i = 0; i < numProductions; i++)
        scanf("%s", grammar[i]);

    // Checking each production rule
    for (i = 0; i < numProductions; i++) {
        symbol = grammar[i][2]; // Get the third character of the production rule

        while (symbol != '\0') { // Loop until the end of the string
            // Checking if the fourth character is one of the allowed operators
            if (grammar[i][3] == '+' || grammar[i][3] == '-' || grammar[i][3] == '*' || grammar[i][3] == '/')
                isValid = 1; // Set isValid flag to true
            else {      
                isValid = 0;
                printErrorMessage(); // Print error message and exit if not a valid operator
            }

            // Check for '$' as it indicates end of the rule
            if (symbol == '$') {
                isValid = 0;
                printErrorMessage();
            }

            // Move to the next character
            symbol = grammar[i][++j];
        }
    }
// INPUT : - Enter the number of production rules: 3
//h=i+j
//k=l*m
//n=o-p

//Operator grammar

    // If isValid is true, it's an operator grammar
    if (isValid == 1)
        printf("Operator grammar");

    return 0;
}
