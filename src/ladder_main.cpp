#include <iostream>
#include <set>
#include <vector>
#include <string>
#include "ladder.h"

using namespace std;

int main() {
    set<string> word_list;
    string dictionary_file = "src/words.txt"; 
    load_words(word_list, dictionary_file);

    if (word_list.empty()) {
        cerr << "Error: Word list is empty or file not found." << endl;
        return 1;
    }

    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;

    if (word_list.find(end_word) == word_list.end()) {
        cerr << "Error: End word is not in the dictionary!" << endl;
        return 1;
    }

    vector<string> word_ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(word_ladder);

    return 0;
}
