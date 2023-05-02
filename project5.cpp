/* 
Michael Sloan
Project #5 - Word Autocomplete using an Alphabet Trie
This project implements an alphabet trie with various methods
located in the Trie.cpp and Trie.h files. A trie object is made
up of an array of TrieNode pointers that points to the next node
in the word. Rather than storing characters in these nodes, the index
of the array plus the ascii value of the char 'a' can tell you what
character is being stored in that node. This main program is a word 
autocomplete application that prompts the user to enter a prefix, and
with the methods written in Trie.cpp, the program tells the user how many
words in the "wordlist.txt" file start with that prefix.
*/
#include "Trie.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

int main()
{
    // trie and vector to hold the prefix list
    Trie myTrie;
    vector<string> myVector;

    // read in file
    ifstream fileIn("wordlist.txt");
    if (fileIn.good()) // make sure we opened the file properly
    {
        string word;
        while (!fileIn.eof())
        {
            fileIn >> word; // insert every word into the trie
            myTrie.insert(word); 
        }
    }
    else {
        cerr << "Couldn't open file!" << endl; // weren't able to open file
    }
    // prefix is what the user entered
    string prefix;
    // how many words start with prefix
    int completions;
    // if user wants to see the completions or not
    string answer;

    do
    {
        cout << "Please enter a word prefix (or press '!' to exit): ";
        cin >> prefix;
        // conditional to end program
        if (prefix.front() == '!')
        {
            break;
        }

        completions = myTrie.completeCount(prefix);
        cout << "There are " << completions << " completions for the prefix '" << prefix << "'. Show completions? ";
        cin >> answer;

        // https://www.delftstack.com/howto/cpp/compare-strings-ignore-case-cpp/
        // where i learned how to ignore case
        if (strcasecmp(answer.c_str(), "yes") == 0)
        {   // getting the vector set up
            myVector = myTrie.complete(prefix);
            cout << endl;
            cout << "Completions" << endl;
            cout << "-----------" << endl;
            // printing each word in the vector
            for (string word: myVector)
            {
                cout << word << endl;
            }
            cout << endl;
        }

    } while (true);

    return 0;
}