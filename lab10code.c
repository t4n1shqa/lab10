#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Tanishqa Sahay
//Dr. Torosdagli
//Lab Assignment 10

struct TrieNode {
    int count;
    struct TrieNode *children[26];
};

void insert(struct TrieNode **ppTrie, char *word);
int numberOfOccurances(struct TrieNode *pTrie, char *word);
struct TrieNode *deallocateTrie(struct TrieNode *pTrie);

//inserts a tree
void insert(struct TrieNode **ppTrie, char *word) {
    if (*ppTrie == NULL) {
        //create if null
        *ppTrie = (struct TrieNode *)malloc(sizeof(struct TrieNode));
        (*ppTrie)->count = 0;
        //initialize all to null
        for (int i = 0; i < 26; i++) {
            (*ppTrie)->children[i] = NULL;
        }
    }
    struct TrieNode *x = *ppTrie;
    for (int i = 0; i < strlen(word); i++) {
        //see if it exists, create it if not
        int y = word[i] - 'a';
        //create if null
        if (x->children[y] == NULL) {
            x->children[y] = (struct TrieNode *)malloc(sizeof(struct TrieNode));
            x->children[y]->count = 0;
            for (int j = 0; j < 26; j++) {
                x->children[y]->children[j] = NULL;
            }
        }
        x = x->children[y];
    }
    x->count++;
}

//counts the number of occurances
int numberOfOccurances(struct TrieNode *pTrie, char *word) {
    if (pTrie == NULL) {
        return 0;
    }
    struct TrieNode *x = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int j = word[i] - 'a';
        if (x->children[j] == NULL) {
            //return 0 if not found
            return 0;
        }
        //check others
        x = x->children[j];
    }
    return x->count;
}

//delete allocated memory
struct TrieNode *deallocateTrie(struct TrieNode *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        //recursive implementation
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void)
{
    struct TrieNode *trie = NULL;
    // read the number of words in the dictionary
    // parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
        printf("%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    //checks that memory was freed
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}



