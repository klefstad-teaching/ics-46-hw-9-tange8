#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg)
{
	cout << "Error: " << word1 << ' ' << word2 << ' ' << msg << endl;
}

//this function checks if the two words are adj, if they differ by one char
//will be used to swap a char 
bool is_adjacent(const string& word1, const string& word2) {
    if (word1.length() != word2.length()) return false; //the words are not the same length

    int count = 0;
    for (size_t i = 0; i < word1.length(); i++) { //loop thru words and check if only the current ind equal
        if (word1[i] != word2[i]) {
            count++;
            if (count > 1) return false; //they don't differ by one
        }
    }
    return count == 1; //this should return true or false
}

//checks and computes the editing distance between two strings based on given d
bool edit_distance_within(const string& str1, const string& str2, int d)
{
   int len1 = str1.length();
    int len2 = str2.length();

    //check if the differnece b/w two string is > d so not possible, reutrn false
    if (abs(len1 - len2) > d) {
        return false;
    }

    //this table will be the min edit distance between the two strings
    vector<vector<int>> myVector(len1 + 1, vector<int>(len2 + 1, 0));

    //base cases 
    for (int i = 0; i <= len1; ++i) myVector[i][0] = i; //first i chars of string 1 will become emtying strings which reqs i deletions
    for (int j = 0; j <= len2; ++j) myVector[0][j] = j; //turning empty strings into first j chars will req j insertions

    //filling in the table
    //for each i and j, if the chars match, js copy the diagonal vlaue
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) { //if it doesn't matcha, choose bes toption between insert, delte, sub
            if (str1[i - 1] == str2[j - 1]) {
                myVector[i][j] = myVector[i - 1][j - 1];
            } else {
                myVector[i][j] = 1 + min({myVector[i - 1][j], myVector[i][j - 1], myVector[i - 1][j - 1]}); //add one after taking min
            }
        }
    }
    return myVector[len1][len2] <= d; //return the checj
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if (word_list.find(end_word) == word_list.end()) {
        return {};  // word is not in the dict, so ladder isn't possible 
    }
    //create a queue vector and push in the words
    //also create a string to track if it's been visited
	queue<vector<string>> ladderqueue;
    ladderqueue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladderqueue.empty()) { //keeo going until there;s no more ladders
        int level_size = ladderqueue.size(); //size of current level
        set<string> current_words; //words added at this current level

        for (int i = 0; i < level_size; ++i) { //process the current ladders at this level
            vector<string> ladder = ladderqueue.front();
            ladderqueue.pop();
            string last_word = ladder.back();

            for (const string& word : word_list) { //explore the neighbors using words list but checking if it's not recycling
                if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) return new_ladder; //return immediately if word == endword bc SHORTEST PATH

                    ladderqueue.push(new_ladder); //else push to the queue to exp;lore more and 
                    current_words.insert(word);
                }
            }
        }

        //make sure to track it as visited
        visited.insert(current_words.begin(), current_words.end());
    }

    return {}; //no ladder was found so empty vector
}

void load_words(set<string>& word_list, const string& file_name)
{
	 ifstream in(file_name);
    if (!in) {
        cerr << "Error: Cannot open file " << file_name << endl;
        return;
    }

    string word;
    while (in >> word) {
        word_list.insert(word);
    }

    in.close();
}

void print_word_ladder(const vector<string>& ladder)
{
	 if (!ladder.empty()) {
        cout << "Word ladder found: ";
        for (const string& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    } else {
        cout << "No word ladder found." << endl;
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

     set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}