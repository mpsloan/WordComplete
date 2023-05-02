#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Trie
{
    private:

        class TrieNode
        {
            public:
                /* initializing all the pointers to null to start
                 added one extra spot in the array that represents
                 the terminating character of a word */
                TrieNode* alphabet[27] = {nullptr};

                /// @brief default constructor
                TrieNode(){}

                ~TrieNode()
                {
                    for (int i = 0; i < 27; i++)
                    {
                        alphabet[i] = nullptr;
                    }
                }
        };

        // root of the trie, number of nodes,
        // and number of words
        TrieNode* root;
        int size; 
        int wordCount;
    
    public:

        /// @brief default constructor
        Trie();

        /// @brief creates an independent copy of myTrie
        /// @param myTrie the trie that is being copied
        Trie(const Trie& myTrie);

        /// @brief Recursive helper to copy a trie 
        /// @param copyFrom node that you are copying from
        /// @param copyInto node that you are copying to
        void copyNodes(TrieNode* copyFrom, TrieNode* copyInto);

        /// @brief deletes all of the nodes in the trie
        ~Trie();
        
        /// @brief recursive helper for the destructor to delete
        /// every node in the trie starting at the passed in node
        /// @param node deletes everything this node is pointing to
        /// and all of its children recursively
        void deleteNodes(TrieNode* node);

        /// @brief removes all contents of the current trie and makes
        /// an independent copy of myTrie
        /// @param myTrie trie that is being copied
        /// @return independent copy of myTrie
        Trie& operator=(const Trie& myTrie);

        /// @brief Inserts a new word into the trie. Duplicate words are not allowed
        /// @param word word that is being added into the trie
        /// @return true if the word was sucessfully added to the trie
        /// false if the word is already in the trie
        bool insert(string word);

        /// @brief get the number of words in the trie
        /// @return number of words in the trie
        int count();

        /// @brief get the total number of nodes in the trie
        /// @return total number of nodes in the trie
        int getSize();

        /// @brief searches the trie for a word
        /// @param word word that the trie is being searched for
        /// @return true if the word was found, false if it wasn't
        bool find(string word);

        /// @brief finds the number of words in the dictionary that 
        /// begin with the given input string
        /// @param prefix word prefix or whole word
        /// @return number of words found with the given string, if 
        /// no matches it returns zero
        int completeCount(string prefix);

        /// @brief gets all the words in the dictionary that begin
        /// with the prefix and puts them in a vector
        /// @param prefix word prefix or whole word
        /// @return a vector containing all of the in the dictionary
        /// that begin with prefix
        vector<string> complete(string prefix);

        /// @brief recursive helper to get all the words that begin with the
        /// given prefix in the dictionary
        /// @param current current node we are at 
        /// @param prefix prefix of the words we are looking for
        /// @param suffix end of the word that the method alters recursively
        /// @param myVector vector reference that will hold all the words with the given prefix
        void completeHelper(TrieNode* current, string prefix, string suffix, vector<string> &myVector);

};