#include <stdio.h>
#include <string.h>

#define SUCCESS 1
#define FAILED 0

int parseExpression(), parseExpressionPrime(), parseTerm(), parseTermPrime(), parseFactor();

const char *current_position;
char input_string[64];

int main() {
    puts("Please input the string to parse:");
    sscanf("i+(i+i)*i", "%s", input_string);
    current_position = input_string;
    puts("\nInput          Action");
    puts("--------------------------------");

    if (parseExpression() && *current_position == '\0') {
        puts("--------------------------------");
        puts("String successfully parsed.");
        return 0;
    } else {
        puts("--------------------------------");
        puts("Error encountered while parsing the string.");
        return 1;
    }
}

int parseExpression() {
    printf("%-16s E -> T E'\n", current_position);
    if (parseTerm()) {
        if (parseExpressionPrime())
            return SUCCESS;
        else
            return FAILED;
    } else
        return FAILED;
}

int parseExpressionPrime() {
    if (*current_position == '+') {
        printf("%-16s E' -> + T E'\n", current_position);
        current_position++;
        if (parseTerm()) {
            if (parseExpressionPrime())
                return SUCCESS;
            else
                return FAILED;
        } else
            return FAILED;
    } else {
        printf("%-16s E' -> $\n", current_position);
        return SUCCESS;
    }
}

int parseTerm() {
    printf("%-16s T -> F T'\n", current_position);
    if (parseFactor()) {
        if (parseTermPrime())
            return SUCCESS;
        else
            return FAILED;
    } else
        return FAILED;
}

int parseTermPrime() {
    if (*current_position == '*') {
        printf("%-16s T' -> * F T'\n", current_position);
        current_position++;
        if (parseFactor()) {
            if (parseTermPrime())
                return SUCCESS;
            else
                return FAILED;
        } else
            return FAILED;
    } else {
        printf("%-16s T' -> $\n", current_position);
        return SUCCESS;
    }
}

int parseFactor() {
    if (*current_position == '(') {
        printf("%-16s F -> ( E )\n", current_position);
        current_position++;
        if (parseExpression()) {
            if (*current_position == ')') {
                current_position++;
                return SUCCESS;
            } else
                return FAILED;
        } else
            return FAILED;
    } else if (*current_position == 'i') {
        current_position++;
        printf("%-16s F -> i\n", current_position);
        return SUCCESS;
    } else
        return FAILED;
}
