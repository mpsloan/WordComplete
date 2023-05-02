#include "Trie.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


Trie::Trie(): // every trie must have a root
root(new TrieNode()),
size(1),
wordCount(0)
{}

Trie::Trie(const Trie &myTrie): // same initialization as copy constructor
root(new TrieNode()),
size(1),
wordCount(0)
{   // call to recursive copy function
    copyNodes(myTrie.root, root);
}

void Trie::copyNodes(TrieNode* copyFrom, TrieNode* copyInto)
{   // cycle through alphabet array
    for (int i = 0; i < 27; i++)
    {   /*  if node you are copying from is pointing to end of word
            make the node you are copying to point to a new node
            and update the size of the trie and number of words */
        if (copyFrom->alphabet[i] && i == 26)
        {
            copyInto->alphabet[i] = new TrieNode();
            ++size;
            ++wordCount;
        } /* else if pointing to a node that isn't end of the word
             make the node you are copying into point to a new node
             and call the recursive method on the new node */
        else if (copyFrom->alphabet[i])
        {
            copyInto->alphabet[i] = new TrieNode();
            ++size;
            copyNodes(copyFrom->alphabet[i], copyInto->alphabet[i]);
        }
    }
}

Trie::~Trie()
{   // call to recursive delete function
    deleteNodes(root);
}

void Trie::deleteNodes(TrieNode* deleteMe)
{   // cycle through alphabet array
    for (int i = 0; i < 27; i++)
    {   
        if (deleteMe->alphabet[i])
        {   /* recursively call deleteNodes on the node it is pointing to
            and delete that same node once it's subtree is deleted */
            deleteNodes(deleteMe->alphabet[i]);
            delete deleteMe->alphabet[i];
            --size;
        }
    }
    // code to delete the root once every other node is deleted
    if (size == 1)
    {
        delete root;
        --size;
        wordCount = 0;
    }
}

Trie &Trie::operator=(const Trie &myTrie)
{   // deleting the current trie and root
    deleteNodes(root);
    // creating a new root
    root = new TrieNode();
    ++size;
    // copying all the nodes from the passed in trie
    copyNodes(myTrie.root, root);

    return *this;
}

bool Trie::insert(string word)
{   
    // variable to hold index of current letter
    int index;
    TrieNode* current = root;

    // cycle through the word
    for (int i = 0; i < word.length(); i++)
    {   // index = character at i ascii - a ascii value 
        index = word.at(i) - 'a';
        // if no pointer to a node at the index, add a node
        if (!current->alphabet[index])
        {
            current->alphabet[index] = new TrieNode();
            ++size;
        }
        // move current to the next node to continue cycle
        current = current->alphabet[index];
    }   /* if the last index in array isn't pointing to anything
         add the node to indicate end of the string and a word
         was added successfully */
    if (!current->alphabet[26])
    {
        current->alphabet[26] = new TrieNode();
        ++size;
        ++wordCount;
        return true;
    }
    else // word is already in trie
    {
        return false;
    }
}

int Trie::count()
{
    return wordCount;
}

int Trie::getSize()
{
    return size;
}

bool Trie::find(string word)
{// very similar logic to insert method
    int index;
    TrieNode* current = root;

    // cycle through the word
    for (int i = 0; i < word.length(); i++)
    {   // index = character at i ascii - a ascii value 
        index = word.at(i) - 'a';
        /*  if no pointer to a node at the index, word isn't in the trie
            therefore return false */
        if (!current->alphabet[index])
        {
            return false;
        }
        else 
        { // else move current to the next node to check for next character
            current = current->alphabet[index];
        }
    }   /* if the last index in array isn't pointing to anything
         after the word is cycled through, then the exact word
         isn't in the trie */
    if (!current->alphabet[26])
    {
        return false;
    }
    else // word is already in trie
    {
        return true;
    }
}

int Trie::completeCount(string prefix)
{   // return the size of the vector
    // after doing the complete function
    vector<string> myVector;
    myVector = complete(prefix);
    return myVector.size();
    
}

vector<string> Trie::complete(string prefix)
{
    vector<string> myVector;
    int index;
    TrieNode* current = root;
    // cycle to the end of the prefix 
    for (int i = 0; i < prefix.length(); i++)
    {
        index = prefix.at(i) - 'a';
        /* if this is true, then no word with that prefix
           return empty vector */
        if (!current->alphabet[index])
        {
            return myVector;
        }
        else 
        {   // else cycle to the next node
            current = current->alphabet[index];
        }
    }
    // call recursive method to fill up vector
    completeHelper(current, prefix, "", myVector);
    return myVector;
}

void Trie::completeHelper(TrieNode* current, string prefix, string suffix, vector<string> &myVector)
{   // cycle through array of pointers for each node
    for (int i = 0; i < 27; i++)
    {   // if pointing to end of word node, combine prefix and suffix to make the word
        if (current->alphabet[i] && i == 26)
        {
            myVector.push_back(prefix + suffix);
        } /* Else if pointing to node that is not end of the word,
             add the character to suffix and recursively call method on the
             rest of the word. After the method is called, pop back off the
             suffix to prepare for a different word */
        else if (current->alphabet[i])
        {
            suffix.push_back(char(i + 'a'));
            completeHelper(current->alphabet[i], prefix, suffix, myVector);
            suffix.pop_back();
        }       
    }
}