# WordComplete

* This project implements an alphabet trie with various methods
located in the Trie.cpp and Trie.h files. 

* A trie object is made up of an array of TrieNode pointers that points to the next node
in the word. Rather than storing characters in these nodes, the index
of the array plus the ascii value of the char 'a' can tell you what
character is being stored in that node. 

* This main program is a word 
autocomplete application that prompts the user to enter a prefix, and
with the methods written in Trie.cpp, the program tells the user how many
words in the "wordlist.txt" file start with that prefix.
