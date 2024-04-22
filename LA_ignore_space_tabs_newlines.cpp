#include <bits/stdc++.h>
#include <array>
using namespace std;

void inp(vector<int> v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
}

bool isWhitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

string removeSingleLineComments(string& input) {
    string result;
    size_t i = 0;

    while (i < input.size()) {
        if (input[i] == '/' && i + 1 < input.size() && input[i + 1] == '/') {
            while (i < input.size() && input[i] != '\n') {
                i++;
            }
        } else {
            result += input[i];
            i++;
        }
    }
    return result;
}

string removeMultiLineComments(string& input) {
    std::string result;
    size_t i = 0;

    while (i < input.size()) {
        if (input[i] == '/' && i + 1 < input.size() && input[i + 1] == '*') {
            while (i + 1 < input.size() && !(input[i] == '*' && input[i + 1] == '/')) {
                i++;
            }
            i += 2;
        } else {
            result += input[i];
            i++;
        }
    }
    return result;
}

string removeStringsAndCount(string& input, int& stringCount) {
    string result;
    size_t i = 0;
    stringCount = 0;
    while (i < input.size()) {
        if (isWhitespace(input[i])) {
            result += input[i];
            i++;
            continue;
        }
        if (isalpha(input[i])) {
            while (isalnum(input[i])) {
                result += input[i];
                i++;
            }
        } else if (isdigit(input[i])) {
            while (isdigit(input[i])) {
                result += input[i];
                i++;
            }
        } else if (input[i] == '\"') {
            stringCount++;
            result += ' ';
            i++;

            while (i < input.size() && input[i] != '\"') {
                result += ' ';
                i++;
            }

            if (i < input.size()) {
                result += ' ';  
                i++;
            }
        } else {
            result += input[i];
            i++;
        }
    }

    return result;
}

string removeIdentifiersAndCount(const std::string& input, int& identifierCount) {
    std::string result;
    size_t i = 0;
    identifierCount = 0;

    while (i < input.size()) {
        if (isWhitespace(input[i])) {
            result += input[i];
            i++;
            continue;
        }
        if (isalpha(input[i]) || input[i] == '_') {
            identifierCount++;
            while (isalnum(input[i]) || input[i] == '_') {
                result += ' ';
                i++;
            }
        } else {
            result += input[i];
            i++;
        }
    }

    return result;
}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

bool isValidFloatChar(char c) {
    return (isDigit(c) || c == '.' || c == 'e' || c == 'E' || c == '-' || c == '+');
}

string removeConstantsAndCount(string& input, int& constantCount) {
    string result;
    size_t i = 0;
    constantCount = 0;

    while (i < input.size()) {
        if (isWhitespace(input[i])) {
            result += input[i];
            i++;
            continue;
        }
        if (isDigit(input[i])) {
            constantCount++;
            while (isDigit(input[i])) {
                result += ' '; 
                i++;
            }
        } else if (input[i] == '.' && i + 1 < input.size() && isDigit(input[i + 1])) {
            constantCount++;
            result += input[i];
            i++;

            while (i < input.size() && isValidFloatChar(input[i])) {
                result += ' ';
                i++;
            }
        } else {
            result += input[i];
            i++;
        }
    }
    return result;
}

bool isKeyword(string& word) {
    unordered_set<std::string> keywords = {
        "int", "float", "char", "double", "void", "if", "else", "while", "for", "return"
    };
    return keywords.find(word) != keywords.end();
}

string removeKeywordsAndCount(const std::string& input, int& keywordCount) {
    string result;
    size_t i = 0;
    keywordCount = 0;

    while (i < input.size()) {
        if (isWhitespace(input[i])) {
            result += input[i];
            i++;
            continue;
        }
        if (isalpha(input[i])) {
            std::string word;
            while (isalnum(input[i]) || input[i] == '_') {
                word += input[i];
                i++;
            }

            if (isKeyword(word)) {
                keywordCount++;
                result += ' ';
            } else {
                result += word;
            }
        } else {
            result += input[i];
            i++;
        }
    }
    return result;
}

bool isSpecialSymbol(char c) {
    unordered_set<char> specialSymbols = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '=', '{', '}', '[', ']', ':', ';', '<', '>', ',', '.', '?', '/'};
    return specialSymbols.find(c) != specialSymbols.end();
}

string removeSpecialSymbolsAndCount(string& input, int& specialSymbolCount) {
    string result;
    size_t i = 0;
    specialSymbolCount = 0;

    while (i < input.size()) {
        if (isWhitespace(input[i])) {
            result += input[i];
            i++;
            continue;
        }

        if (isSpecialSymbol(input[i])) {
            specialSymbolCount++;
            result += ' ';
            i++;
        } else {
            result += input[i];
            i++;
        }
    }

    return result;
}

bool isOperator(char c) {
    unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>', '&', '|', '!', '^', '%'};
    return operators.find(c) != operators.end();
}

int lexCode(string code){
    int noOfOperators=0,noOfString=0,noOfConstant=0,noOfIdentifier=0,noOfkeywords=0,noOfSpecialSymbol=0;
    code=removeSingleLineComments(code);
    code=removeMultiLineComments(code);
    code=removeConstantsAndCount(code,noOfConstant);
    code=removeStringsAndCount(code,noOfString);
    code=removeKeywordsAndCount(code,noOfkeywords);
    code=removeIdentifiersAndCount(code,noOfIdentifier);
    code=removeSpecialSymbolsAndCount(code,noOfSpecialSymbol);
    //number of operator
    for (int i=0;i<code.size();i++){
        if(isOperator(code[i])){noOfOperators++;}
    }
    cout<<"number of string: "<<noOfString<<endl;
    cout<<"number of constants: "<<noOfConstant<<endl;
    cout<<"number of identifier: "<<noOfIdentifier<<endl;
    cout<<"number of operators in the code: "<<noOfOperators<<endl;
    cout<<"number of keywords in the code: "<<noOfkeywords<<endl;
    cout<<"number of special symbol in the code: "<<noOfSpecialSymbol<<endl;
    cout<<code<<endl;
    return noOfSpecialSymbol+noOfConstant+noOfIdentifier+noOfkeywords+noOfOperators+noOfString;
    
}

int main()
{
    string inputCode = "int a = b + c;";
    int tokens=lexCode(inputCode);


    cout<<"total number of tokens: "<<tokens;
    return 0;
}