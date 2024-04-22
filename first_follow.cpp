#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

void computeFirst(map<char, set<char>>& first, const map<char, vector<string>>& grammar) {
    for (auto const& entry : grammar) {
        char nonTerminal = entry.first;
        const vector<string>& productions = entry.second;

        for (auto const& production : productions) {
            char symbol = production[0];
            if (islower(symbol) || symbol == 'e') { 
                first[nonTerminal].insert(symbol);
            } else { 
                for (char s : first[symbol]) {
                    first[nonTerminal].insert(s);
                }
            }
        }
    }
}


void computeFollow(map<char, set<char>>& follow, const map<char, vector<string>>& grammar, const map<char, set<char>>& first, char startSymbol) {
    follow[startSymbol].insert('$'); 

    bool changed = true;
    while (changed) {
        changed = false;
        for (auto const& entry : grammar) {
            char nonTerminal = entry.first;
            const vector<string>& productions = entry.second;

            for (auto const& production : productions) {
                for (size_t i = 0; i < production.length(); ++i) {
                    char symbol = production[i];
                    if (isupper(symbol)) { 
                        char nextSymbol = (i == production.length() - 1) ? '!' : production[i + 1]; 
                        if (islower(nextSymbol)) { 
                            follow[symbol].insert(nextSymbol);
                        } else if (isupper(nextSymbol)) { 
                            for (char s : first.at(nextSymbol)) {
                                if (s != 'e') {
                                    if (follow[symbol].find(s) == follow[symbol].end()) {
                                        follow[symbol].insert(s);
                                        changed = true;
                                    }
                                }
                            }
                            if (first.at(nextSymbol).find('e') != first.at(nextSymbol).end() || nextSymbol == '!')
                            {
                                for (char s : follow[nonTerminal]) {
                                    if (follow[symbol].find(s) == follow[symbol].end()) {
                                        follow[symbol].insert(s);
                                        changed = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {

    map<char, vector<string>> grammar = {
        {'S', {"AB", "BC"}},
        {'A', {"aA", "e"}},
        {'B', {"bB", "c"}},
        {'C', {"d"}}
    };

    map<char, set<char>> first, follow;


    computeFirst(first, grammar);


    computeFollow(follow, grammar, first, 'S');


    cout << "FIRST sets:" << endl;
    for (auto const& entry : first) {
        char nonTerminal = entry.first;
        const set<char>& firstSet = entry.second;

        cout << nonTerminal << ": {";
        for (char symbol : firstSet) {
            cout << symbol << ", ";
        }
        cout << "}" << endl;
    }


    cout << "\nFOLLOW sets:" << endl;
    for (auto const& entry : follow) {
        char nonTerminal = entry.first;
        const set<char>& followSet = entry.second;

        cout << nonTerminal << ": {";
        for (char symbol : followSet) {
            cout << symbol << ", ";
        }
        cout << "}" << endl;
    }

    return 0;
}
