#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "dictionary.h"

// define node structure
typedef struct node
{
    bool is_word;
    struct node* letters[27];
}
node;

// declare global pointers/variables
node* root;
node* cp;
int wordcount;
bool dictloaded;

// my 'free function' prototype
void freefun(node* cp);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // make sure cursor pointer is reset to root
    cp = root; 
    
    // for each letter in input word
    int wordlen = strlen(word) + 1;
    int x;
    int c;
    for (int i = 0; i < wordlen; i++)
    {
        // get letter
        c = word[i];
        
        // convert to 'hash' (to access trie)
        if (c >= 'a' && c <= 'z')
        {
            x = c - 'a';
        }
        else if (c >= 'A' && c <= 'Z')
        {
            x = c - 'A';
        }
        else if (c == '\'')
        {
            x = c - 13;
        }
        else if (c == '\0')
        {
            // check is_word
            if (cp->is_word == true)
            {
                // it's a word
                return true;
            }
            else
            {
                // it's not a word
                return false;
            }
        }
        else
        {
            printf("error in check() input word (from text) contains non-alpha or apost char\n");
            return false;
        }
        
        // go to corresponding 'letter' in trie
        if (cp->letters[x] == NULL)
        {
            // word misspelled
            return false;
        }
        else
        {
            // go to next node in trie
            cp = cp->letters[x];
        }
    }
    // if gets to here, something has gone wrong
    printf("error - something wrong in check()\n");
    return false;
}

//Load dictionary
bool load(const char* dictionary)
{
    dictloaded = false;
    
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        printf("error in load(): root pointer contains NULL");
        return false;
    }  
    
    // initialise root node to NULL
    root->is_word = NULL;
    for (int i = 0; i < 27; i++)
    {
        root->letters[i] = NULL;
    }
    
    // create pointer to that file
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("error in load(): opening dictionary file returns NULL");
        return false;
    }
    
    // create 'cursor' pointer cp to traverse the trie
    cp = root; 

    // load dictionary into trie
    wordcount = 0;
    int x;
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // if not newline
        if (c != '\n')
        {
            // convert char to our array 'hash'
            if (c >= 'a' && c <= 'z')
            {
                x = c - 'a';
            }
            else if (c == '\'')
            {
                x = c - 13;
            }
            else
            {
                printf("error! does not contain just lowercase letters or apostrophes");
                return false;
            }
            
            if (cp->letters[x] != NULL)
            {
                // set cursor pointer to next node
                cp = cp->letters[x];
            }
            else
            {
                // create new node, address stored at letters[x]
                cp->letters[x] = malloc(sizeof(node));
                
                // check ADDRESS for NULL
                if (cp->letters[x] == NULL)
                {
                    printf("error mallocing subsequent nodes in trie, returns NULL");
                    return false;
                }
                
                // set cursor pointer to new node
                cp = cp->letters[x];
                
                // initialise new node to NULL
                cp->is_word = false;
                for (int i = 0; i < 27; i++)
                {
                    cp->letters[i] = NULL;
                }
            }
        }
        // else if newline
        else 
        {
            // check is_word in newest node
            cp->is_word = true; 
            // reset cursor for next word
            cp = root;
            // update counter
            wordcount++;
        }        
    }
    
    // close dicionary file
    fclose(fp);
    
    dictloaded = true;
    return true;
}

//Returns number of words in dictionary if it is loaded, otherwise 0

unsigned int size(void)
{
    if (dictloaded == true)
    {
        return wordcount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory.  Returns true if successful else false.

bool unload(void)
{
    // initialise cp to root
    cp = root;
    
    freefun(cp);
    
    return true;
}

void freefun(node* cp)
{
    for (int i = 0; i < 27; i++)
    {
        if (cp->letters[i] != NULL)
        {
            freefun(cp->letters[i]);
        }
    }
    free(cp);      
}